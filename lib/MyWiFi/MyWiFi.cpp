#include "MyWiFi.h"

#include <Arduino.h>

bool isMaster = false;

void setupWifi(bool configLoad) {
  WiFi.disconnect(true, true);  // Reset Wi-Fi config.
  WiFi.mode(configLoad ? WIFI_AP_STA : WIFI_STA);
  if (configLoad) {
    connectWifi();
  } else {
    startAP();
  }
}

bool connectWifi() {
  if (connectWifi(true, "WifiF", "-")) {
    isMaster = true;
    return true;
  }

  isMaster = false;
  return connectWifi(true, "WifidoKPT", "-");
}

bool connectWifi(bool disconnect, char *ssid, char *password) {
  if (disconnect) {
    Serial.println("disconnect");
    WiFi.disconnect(true, true);
    WiFi.mode(WIFI_STA);
  }

  WiFi.begin(ssid, password);
  Serial.printf("Connect to %s\n", ssid);

  int attempts = 0;

  wl_status_t status = WiFi.status();
  while ((status == WL_DISCONNECTED || status == WL_IDLE_STATUS) &&
         attempts < MYWIFI_MAX_ATTEMPTS) {
    if (status == WL_DISCONNECTED) attempts++;

    delay(500);
    status = WiFi.status();
  }

  if (status != WL_CONNECTED) {
    Serial.printf("Fail to Connect %s: %s\n", ssid, getStatusError(status));
    return false;
  }

  Serial.printf("Connected %s: ", ssid);
  Serial.print(WiFi.localIP());
  Serial.print(" - ");
  Serial.println(WiFi.softAPmacAddress());
  return true;
}

int checkWifi() {
  bool connected = WiFi.status() == WL_CONNECTED;

  // WiFi conectado no Principal (não fazer nada)
  if (connected && isMaster) return MYWIFI_CONNECTED;

  // WiFi está conectado no BackUp e a master offline (não fazer nada)
  if (connected && checkMasterWifi() == MYWIFI_MASTER_OFF) {
    return MYWIFI_CONNECTED_BACKUP;
  }

  // Reconectar o WiFi, motivos:
  // - WiFi Desconectado
  // - Conectado no 'WiFi BackUp' mas o 'WiFi Master' voltou
  return connectWifi()
             ? MYWIFI_ERROR
             : (isMaster ? MYWIFI_CONNECTED : MYWIFI_CONNECTED_BACKUP);
}

bool checkMasterWifi() { return MYWIFI_MASTER_OFF; }

/**
 * Converte o "Código de Erro (wl_status_t)" em String
 **/
const char *getStatusError(wl_status_t status) {
  if (status == WL_NO_SHIELD) return "WL_NO_SHIELD";
  if (status == WL_IDLE_STATUS) return "WL_IDLE_STATUS";
  if (status == WL_NO_SSID_AVAIL) return "WL_NO_SSID_AVAIL";
  if (status == WL_SCAN_COMPLETED) return "WL_SCAN_COMPLETED";
  if (status == WL_CONNECTED) return "WL_CONNECTED";
  if (status == WL_CONNECT_FAILED) return "WL_CONNECT_FAILED";
  if (status == WL_CONNECTION_LOST) return "WL_CONNECTION_LOST";
  if (status == WL_DISCONNECTED) return "WL_DISCONNECTED";
  return "UNK";
}

/**
 * Configura o Wi-Fi do ESP32 em modo Access Point (AP)
 * Com isso é possivel acessar o mesmo para configurar
 **/
void startAP() {
  WiFi.softAP(MYWIFI_AP_SSID, MYWIFI_AP_PASSWORD, 1, 0, 2);
  WiFi.softAPsetHostname("cervejeira.config");
  IPAddress IP = WiFi.softAPIP();

  Serial.println("Wi-Fi de configuração Iniciado!");
  Serial.printf("SSID: %s\n", MYWIFI_AP_SSID);
  Serial.printf("Password: %s\n", MYWIFI_AP_PASSWORD ? MYWIFI_AP_PASSWORD : "");
  Serial.print("IP: ");
  Serial.println(IP);
}