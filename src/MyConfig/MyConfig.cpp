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