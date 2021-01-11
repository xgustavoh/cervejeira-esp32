// SPIFFS
#ifndef __MYCONFIG_H__
#define __MYCONFIG_H__

#include <SPIFFS.h>

#include "./include/Defines.h"
#include "./include/Structs.h"

/**
 * Inicia a Configuração do SPIFFS
 **/
bool setupConfig();

/**
 * Carrega as configurações salva na memoria
 **/
bool loadConfig();

/**
 * Salva as configurações
 **/
bool saveConfig();

#endif  // __MYCONFIG_H__