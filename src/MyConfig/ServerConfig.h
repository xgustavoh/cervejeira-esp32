#ifndef __SERVERCONFIG_H__
#define __SERVERCONFIG_H__

#include <WiFi.h>

/**
 * Inicia o Servidor de configuração
 * Função fica em LOOP até que a configuração do Wi-Fi seja atribuida
 **/
void startServer();

/**
 *  Get POST Data
 **/
String getBodyData(String* header);

/**
 * Faz o Controle de Rota do Server
 **/
void routerServer(String* header, WiFiClient* client);

/**
 * Send Header Status 200
 **/
void sendHeader200(WiFiClient* client);

/**
 * Send Header Status 404
 **/
void sendHeader404(WiFiClient* client);

/**
 * Send Config Page
 **/
void sendBodyConfig(WiFiClient* client, bool error);

/**
 * Send Sucess Page
 **/
void sendBodySuccess(WiFiClient* client);

#endif  // __SERVERCONFIG_H__