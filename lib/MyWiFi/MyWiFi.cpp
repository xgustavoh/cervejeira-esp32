#include "MyWiFi.h"

#include <Arduino.h>

bool isMaster = false;

WifiConfig *_master = NULL;
WifiConfig *_backup = NULL;

void setupWifi(bool isAP, WifiConfig *master, WifiConfig *backup) {
  // Atribue a Variavel Global as configurações
  _master = master;
  _backup = backup;

  WiFi.disconnect(true, true);  // Reset Wi-Fi config.
  WiFi.mode(isAP ? WIFI_AP_STA : WIFI_STA);
  if (!isAP) {
    connectWifi();
  } else {
    startAP();
  }
}

bool connectWifi() {
  if (_master != NULL && _master->ssid[0] != '\0' &&
      connectWifi(true, _master->ssid, _master->password)) {
    isMaster = true;
    return true;
  }

  isMaster = false;
  return _backup != NULL && _backup->ssid[0] != '\0' &&
         connectWifi(true, _backup->ssid, _backup->password);
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
  while ((status == WL_DISCONNECTED || status == WL_IDLE_STATUS ||
          status == WL_NO_SHIELD) &&
         attempts < MYWIFI_MAX_ATTEMPTS) {
    // Contador de Tentativas ("timeout")
    if (status != WL_IDLE_STATUS)
      attempts++;
    else if (attempts > 0)
      attempts = 0;

    delay(500);
    status = WiFi.status();
  }

  if (status != WL_CONNECTED) {
    WiFi.disconnect(false, false);
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
  return connectWifi() ? (isMaster ? MYWIFI_CONNECTED : MYWIFI_CONNECTED_BACKUP)
                       : MYWIFI_ERROR;
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
  WiFi.softAPsetHostname("cervejeira.local");
  IPAddress IP = WiFi.softAPIP();

  Serial.println("Wi-Fi de configuração Iniciado!");
  Serial.printf("SSID: %s\n", MYWIFI_AP_SSID);
  Serial.printf("Password: %s\n", MYWIFI_AP_PASSWORD ? MYWIFI_AP_PASSWORD : "");
  Serial.print("IP: ");
  Serial.println(IP);
}