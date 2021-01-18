// SPIFFS
#ifndef __MYMQTT_H__
#define __MYMQTT_H__

#include <PubSubClient.h>
#include <WiFi.h>

#include "./include/Defines.h"
// #include "./include/Structs.h"

/**
 * Inicia a Configuração do SPIFFS
 **/
void setupMQTT();

/**
 * Faz a conexão com o servidor MQTT
 **/
bool connectMQTT();

/**
 * Verifica a conexão com o Broker.
 **/
bool checkBroker();

/**
 * Fução de callback do MQTT.
 * É a função responsavel pelo recebimento dos dados do servidor.
 **/
void recv_broker(char* topic, byte* payload, unsigned int length);

/**
 * Envia para o servidor MQTT as informações coletadas.
 **/
void send_broker();

/**
 * Event Loop, responsavel por aguardar uma resposta do servidor, e processar
 *ela.
 **/
void loop_broker();

#endif  // __MYMQTT_H__