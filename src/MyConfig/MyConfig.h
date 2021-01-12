// SPIFFS
#ifndef __MYCONFIG_H__
#define __MYCONFIG_H__

#include <SPIFFS.h>

#include "./include/Defines.h"
#include "./include/Structs.h"

/**
 * Inicia a Configuração do SPIFFS
 **/
bool setupConfig(ConfigFile *FConfig);

/**
 * Carrega as configurações salva na memoria
 **/
bool loadConfig(ConfigFile *FConfig);

/**
 * Salva as configurações
 **/
bool saveConfig(ConfigFile *FConfig);

/**
 * Atualiza a configura do Wi-Fi
 **/
bool updateWiFi(ConfigFile *FConfig, char *ssid, char *password, char *ipCheck,
                bool isBackup);

#endif  // __MYCONFIG_H__