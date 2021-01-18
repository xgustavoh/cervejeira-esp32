#include <Arduino.h>
#include <MyWifi.h>

#include "MyConfig/MyConfig.h"
#include "MyConfig/ServerConfig.h"
#include "MyMQTT/MyMQTT.h"

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
  setupMQTT();
}

void loop() {
  // Verifica se o WiFi está Ok!
  if (checkWifi() != MYWIFI_ERROR) {
    // Verifica a conexão com o servidor MQTT
    // Se estiver Conectado, exetuar a Loop do MQTT
    if (checkBroker()) loop_broker();
  }

  // put your main code here, to run repeatedly:
  Serial.println("Loop!");
  delay(5000);
}