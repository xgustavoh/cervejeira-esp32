/**
 * Arquivo de Estrutura do Wi-Fi
 **/

#ifndef __MYWIFI_STRUCTS_H__
#define __MYWIFI_STRUCTS_H__

/**
 * Wi-Fi Struct
 * Contem todas informações necessaria para conexão.
 **/
struct WifiConfig {
  char ssid[32];      // Identificação do WiFi
  char password[63];  // Senha do WiFi
  char ipCheck[15];   // IP do Roteador
};

#endif  // __MYWIFI_STRUCTS_H__
