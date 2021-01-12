/**
 * Arquivo de Definições do SPIFFS
 **/

#ifndef __MYCONFIG_DEFINES_H__
#define __MYCONFIG_DEFINES_H__

/**
 * Define oque irá fazer quando não inicia o SPIFFS
 * |- false | Não formatar a unidade (default)
 * |- true  | Formatar a unidade
 **/
#define SPIFFS_FORMAT_ON_FAIL false

/**
 * Nome do Arquivo de Configuração
 **/
#define CONFIG_FILE "/config.bin"

#endif  // __MYCONFIG_DEFINES_H__