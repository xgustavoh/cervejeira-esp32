#include <Arduino.h>
#include <MyWifi.h>

#include "MyConfig/MyConfig.h"

#define LED 27

void setup() {
  Serial.begin(115200);

  if (!setupConfig()) {
    Serial.println("Falha ao iniciar a Configuração");
    while (true) {
      delay(1000);
    }
  }

  if (!loadConfig()) {
    Serial.println("Falha ao ler arquivo de configuração");
    Serial.println("Iniciando Servidor de Configuração");
    // Caso não tenha arquivo de configuração
    // Deve ser criado um!
    setupWifi(false);
    while (true) {
      // Substituir por servidor Web
      // Start Config Server
      delay(1000);
    }
  }

  setupWifi(true);
}

void loop() {
  // Verifica se o WiFi está Ok!
  checkWifi();

  // put your main code here, to run repeatedly:
  Serial.println("Loop!");
  delay(5000);
}