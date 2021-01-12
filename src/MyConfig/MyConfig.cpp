#include "MyConfig.h"

#include <Arduino.h>

ConfigFile FConfig;

bool setupConfig() {
  if (!SPIFFS.begin(SPIFFS_FORMAT_ON_FAIL)) {
    return false;
  }

  memset(&FConfig, 0x00, sizeof(FConfig));
  return true;
}

bool loadConfig() {
  if (!SPIFFS.exists(CONFIG_FILE)) {
    return false;
  }

  File f = SPIFFS.open(CONFIG_FILE, FILE_READ);
  if (!f) {
    return false;
  }

  if (!f.available() || f.size() > sizeof(ConfigFile)) {
    f.close();
    return false;
  }

  memset(&FConfig, 0x00, sizeof(ConfigFile));
  f.readBytes((char *)&FConfig, f.size());
  f.close();
  return true;
}

bool saveConfig() {
  File f = SPIFFS.open(CONFIG_FILE, FILE_WRITE);
  if (!f) {
    return false;
  }

  f.write((byte *)&FConfig, sizeof(ConfigFile));
  f.close();
  return true;
}

// Altera as configurações!
bool updateWiFi(char *ssid, char *password, char *ipCheck, bool isBackup) {
  if (isBackup) {
    memcpy(FConfig.backup.ssid, ssid, 32);
    memcpy(FConfig.backup.password, password, 63);
    if (ipCheck != NULL) {
      memcpy(FConfig.backup.ipCheck, ipCheck, 15);
    } else {
      memset(FConfig.backup.ipCheck, 0x00, 15);
    }
  } else {
    memcpy(FConfig.master.ssid, ssid, 32);
    memcpy(FConfig.master.password, password, 63);
    if (ipCheck != NULL) {
      memcpy(FConfig.master.ipCheck, ipCheck, 15);
    } else {
      memset(FConfig.master.ipCheck, 0x00, 15);
    }
  }

  saveConfig();
}