#include <Arduino.h>
#include <MyWifi.h>

#include "MyConfig/MyConfig.h"
#include "MyConfig/ServerConfig.h"

ConfigFile FConfig;

void setup() {
  Serial.begin(115200);

  if (!setupConfig(&FConfig)) {
    Serial.println("Falha ao iniciar a Configuração");
    while (true) {
      delay(1000);
    }
  }

  if (!loadConfig(&FConfig)) {
    Serial.println("Falha ao ler arquivo de configuração");
    Serial.println("Iniciando Servidor de Configuração");
    // Caso não tenha arquivo de configuração
    // Deve ser criado um!
    setupWifi(true, NULL, NULL);
    startServer(&FConfig);
  }

  setupWifi(false, &FConfig.master, &FConfig.backup);
}

void loop() {
  // Verifica se o WiFi está Ok!
  checkWifi();

  // put your main code here, to run repeatedly:
  Serial.println("Loop!");
  delay(5000);
}