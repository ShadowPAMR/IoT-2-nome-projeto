#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <LoRa.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "BrightStart - AP"
#define WIFI_PASSWORD "brightstart2324"
#define API_KEY "AIzaSyAbXTXPc5VT46wRJr__AjwhMfPcr5xdJKM "
#define DATABASE_URL "https://iotmq135esp32-default-rtdb.europe-west1.firebasedatabase.app/"
#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_SS 18
#define LORA_RST 14
#define LORA_DI0 26
#define LORA_BAND 868E6

int sensorValue;
int digitalValue;
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void disableBrownoutDetector() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
}

void setup() {
  disableBrownoutDetector();
  setCpuFrequencyMhz(80);
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);

  Serial.print("Initializing LoRa...");
  if (!LoRa.begin(LORA_BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read the LoRa packet data
    String loraData = "";
    while (LoRa.available()) {
      loraData += (char)LoRa.read();
    }

    // Send the received data to Firebase
    String path = "/data";
    if (Firebase.RTDB.set(&firebaseData, path.c_str(), loraData.c_str())) {
      Serial.println("Data sent successfully to Firebase: " + loraData);
    } else {
      Serial.println("Failed to send data to Firebase.");
      Serial.println(firebaseData.errorReason());
    }

    // Print the received data and RSSI
    Serial.print("Received packet '");
    Serial.print(loraData);
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}