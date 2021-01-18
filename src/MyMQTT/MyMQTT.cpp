#include "MyMQTT.h"

WiFiClient espClient;
PubSubClient MQTT(espClient);

// ID Unico do Cliente
// Usado para Broker identificar a conexão
char mqttID[60];

/**
 * Inicia a Configuração do SPIFFS
 **/
void setupMQTT() {
  const int macSize = WiFi.macAddress().length();

  MQTT.setServer(MQTT_BROKER_HOST, MQTT_BROKER_PORT);
  MQTT.setCallback(recv_broker);

  memset(mqttID, 0x00, 60);
  WiFi.macAddress().toCharArray(mqttID, macSize, 0x0);
  mqttID[macSize] = '-';
  mqttID[macSize + 1] = 'c';
  mqttID[macSize + 2] = 'e';
  mqttID[macSize + 3] = 'r';
  mqttID[macSize + 4] = 'v';
  mqttID[macSize + 5] = 'e';
  mqttID[macSize + 6] = 'j';
  mqttID[macSize + 7] = 'a';

  // Tenta efetuar a primeira conexão.
  connectMQTT();
}

/**
 * Faz a conexão com o servidor MQTT
 **/
bool connectMQTT() {
  int t = 0;
  while (!MQTT.connected() && t < MQTT_MAX_RECONNECT) {
    t++;
    MQTT.connect(mqttID);
    delay(200);
  }

  return MQTT.connected();
}

/**
 * Verifica a conexão com o Broker.
 **/
bool checkBroker() { return MQTT.connected() ? true : connectMQTT(); }

/**
 * Fução de callback do MQTT.
 * É a função responsavel pelo recebimento dos dados do servidor.
 **/
void recv_broker(char* topic, byte* payload, unsigned int length) {}

/**
 * Envia para o servidor MQTT as informações coletadas.
 **/
void send_broker(const char* topic, const char* payload) {
  MQTT.publish(topic, payload);
}

/**
 * Event Loop, responsavel por aguardar uma resposta do servidor, e processar
 *ela.
 **/
void loop_broker() { MQTT.loop(); }