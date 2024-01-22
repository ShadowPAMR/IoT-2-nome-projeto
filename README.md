## IoT-2-Gestor_de_presenças
Projeto final de IoT

## Colaboradores
- Joaquim Santos
- Pedro Almeida
- David Couteiro

## Descrição do Projeto
O objetivo deste projeto é configurar um sistema de gestão de presenças (entradas e saídas) com informações acessíveis através de uma página web. Os dados serão processados para indicar quando alguém faltou, está de férias, chegou atrasado ou saiu mais cedo do horário estabelecido.

## Tecnologias usadas
- 1 ESP32 ligado ao computador
- 1 ESP32 TTGO 
- RFID RC-522

## Storytelling
- Em um edifício com aproximadamente 30 colaboradores, busca-se implementar um sistema de gestão de presenças, onde as informações serão disponibilizadas online. Cada colaborador receberá uma tag para registrar duas vezes ao dia, na entrada e na saída, por exemplo, às 9:00h e 18:00h. Com base nesses dados, será possível identificar atrasos, ausências e saídas antecipadas.

## Exemplos de Funcionalidades
1. **Atraso na Entrada:** Se alguém registrar a tag após o horário de entrada estipulado, por exemplo, às 9:20h em vez de 9:15h, o sistema emitirá um alerta indicando o atraso ao Coordenador.
2. **Ausência durante o Dia:** Se um colaborador não registrar a tag, será gerado um alerta informando que a pessoa não compareceu ao edifício.

## Aquitetura do projeto
- Sensores e dispositivos utilizados
- Comunicação LoRa

## Justificação de Ausência
O sistema permitirá a justificação da não comparecência do colaborador, evitando assim alertas desnecessários devido à ausência.

## Requisitos de Hardware
- **Sensor NFC:** Responsável pela leitura das tags dos colaboradores.
- **Tag RFID:** Identifica o colaborador associando-se diretamente ao seu nome/perfil.
- **ESP-32:** Suportar o sensor NFC e enviar a informação para o Rhasperry
- **Rhasperry:** Tratar a informação no Node-red; Enviar e guardar a informação no Firebase; Node-red manter ligada a Dashboard (página web)

## Protocolos Utilizados
- **Web Sockets**
- **Firebase**