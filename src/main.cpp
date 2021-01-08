#include <Arduino.h>
#include "MyWiFi/MyWiFi.h"

#define LED 27

void setup() {
  Serial.begin(115200); // Set Clock Processador
  setupWifi();
}

void loop() {
  // Verifica se o WiFi está Ok!
  checkWifi();

  // put your main code here, to run repeatedly:
  Serial.println("Loop!");
  delay(5000);
}