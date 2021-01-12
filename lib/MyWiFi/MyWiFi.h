#ifndef __MYWIFI_H__
#define __MYWIFI_H__

#include <WiFi.h>

#include "./include/Defines.h"
#include "./include/Structs.h"

// Setup WiFi config
void setupWifi(bool isAP, WifiConfig *master, WifiConfig *backup);

// Connect to WiFi
bool connectWifi();
bool connectWifi(bool disconnect, char *ssid, char *password);

// Check WiFi Status
int checkWifi();
bool checkMasterWifi();

/**
 * Converte o "Código de Erro (wl_status_t)" em String
 **/
const char *getStatusError(wl_status_t status);

/**
 * Configura o Wi-Fi do ESP32 em modo Access Point (AP)
 * Com isso é possivel acessar o mesmo para configurar
 **/
void startAP();

#endif  // __MYWIFI_H__