/**
 * Arquivo de Estrutura do SPIFFS
 **/

#ifndef __MYCONFIG_STRUCTS_H__
#define __MYCONFIG_STRUCTS_H__

#include <MyWiFi.h>

struct ConfigFile {
  WifiConfig master;
  WifiConfig backup;
};

#endif  // __MYCONFIG_STRUCTS_H__