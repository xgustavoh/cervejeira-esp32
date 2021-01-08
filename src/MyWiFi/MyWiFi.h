#ifndef __MYWIFI_H__
#define __MYWIFI_H__

#include <WiFi.h>
// #include <PubSubClient.h> -> Pertence ao MTQQ

#define MYWIFI_MAX_ATTEMPTS 10 // Tentativas máxima permitida para conectar no WiFi

#define MYWIFI_ERROR 0
#define MYWIFI_CONNECTED 1
#define MYWIFI_CONNECTED_BACKUP 2
#define MYWIFI_CHANGE_TO_MASTER 5

#define MYWIFI_MASTER_ON 1
#define MYWIFI_MASTER_OFF 0

// Struct Wi-Fi
struct WifiConfig {
  char ssid[32];
  char password[63];
  char ipCheck[15];
};

// Setup WiFi config
void setupWifi();

// Connect to WiFi
bool connectWifi();
bool connectWifi(char *ssid, char *password, bool disconnect);

// Check WiFi Status
int checkWifi();
bool checkMasterWifi();

// Convert wl_status_t in String
const char *getStatusError(wl_status_t status);

extern WifiConfig master;
extern WifiConfig backup;

#endif // __MYWIFI_H__