#include "ServerConfig.h"

#include <MyWiFi.h>

#include "MyConfig.h"

// Criar Servidor da Porta 80
WiFiServer server(80);

// Configurado com Sucesso
bool config = false;

void startServer() {
  server.begin();
  while (!config) {
    WiFiClient client = server.available();
    if (client) {
      Serial.println("Novo cliente conectado!");

      String header = "";
      while (client.connected()) {
        if (client.available() > 0) {
          header += client.readString();
        } else if (header.length() > 0) {
          routerServer(&header, &client);
          client.stop();
        }
      }
    }
  }
}

/**
 * POST Data
 **/
String getBodyData(String* header) {
  String data = "";
  int pos = header->length() - 3;
  while (pos > 0 && header->charAt(pos) != '\n') {
    pos--;
  }
  return header->substring(pos + 1);
}

void getData(String* data, String key, char* ret) {
  int start = data->indexOf(key + "=");
  if (start < 0) {
    ret[0] = '\0';
    return;
  }

  start += key.length() + 1;
  int end = start;
  while (end < data->length() && data->charAt(end) != '\r' &&
         data->charAt(end) != '\n' && data->charAt(end) != '&') {
    end++;
  }

  for (int i = 0, d = start; d < end; i++, d++) ret[i] = data->charAt(d);
}

/**
 * Router
 **/
void routerServer(String* header, WiFiClient* client) {
  if (header->indexOf("GET /favicon.ico") >= 0) {
    sendHeader404(client);
    return;
  }
  Serial.print("HEADER: ");
  Serial.println(*header);

  // Rotas de URL
  sendHeader200(client);
  if (header->indexOf("POST /check-wifi") >= 0) {
    String dataPost = getBodyData(header);
    char ssid[32], password[63];
    for (int i = 0; i < 63; i++) {
      if (i < 32) ssid[i] = '\0';
      password[i] = '\0';
    }

    getData(&dataPost, "ssid", ssid);
    getData(&dataPost, "password", password);
    if (connectWifi(false, ssid, password)) {
      config = true;
      sendBodySuccess(client, ssid);
      WiFi.disconnect(false, false);
      updateWiFi(ssid, password, NULL, false);
    } else {
      sendBodyConfig(client, true);
    }
  } else {
    sendBodyConfig(client, false);
  }
}

/**
 * Headers
 **/
void sendHeader200(WiFiClient* client) {
  // Send HTTP headers "Status 200"
  client->println("HTTP/1.1 200 OK");
  client->println("Content-type:text/html");
  client->println("Connection: close");
  client->println();
}

void sendHeader404(WiFiClient* client) {
  client->println("HTTP/1.1 404 Not Found");
  client->println();
}

/**
 * Page Body
 **/
void sendBodyConfig(WiFiClient* client, bool error) {
  int n = WiFi.scanNetworks();

  client->println("<!DOCTYPE html><html lang=\"pt-br\">");
  client->println(
      "<head><meta charset=\"UTF-8\"><meta name=\"viewport\" "
      "content=\"width=device-width, initial-scale=1.0\">");
  client->println("<title>Configuração - Cervejeira</title><style>");

  client->println("* { border: 0; margin: 0; padding: 0; }");
  client->println(
      "body { color: #fff; background: #535c68; width: 100vw; height: 100vh; "
      "display: flex; text-align: center; align-items: center; "
      "justify-content: center; }");
  client->println(
      "select, input { color: #fff; border: #fff 1px solid; border-radius: "
      "5px; background: transparent; padding: 5px; width: 25vw; "
      "min-width: 300px; margin: 5px 0; "
      "}");
  client->println("h1 { margin-bottom: 0; }");
  client->println("p { margin-bottom: 10px; }");
  client->println("option { color: #000; }");
  client->println(
      "input { width: 23vw; min-width: 280px; padding: 6px 10px; }");
  client->println("input::placeholder { color: #ccc; }");
  client->println(
      "input[type=\"submit\"] { margin: 20px 0; cursor: pointer; "
      "border-color: #079992; background: #38ada9; }");
  client->println("input[type=\"submit\"]:hover { background: #079992; }");

  client->println("</style></head><body>");
  client->println("<form action=\"/check-wifi\" method=\"POST\">");
  client->println(
      "<h1 style=\"margin-bottom: 10px;\">Configuração Inicial</h1>");
  client->println(
      "<p style=\"margin-bottom: 20px;\">Escolha o Wi-Fi para a Cervejeira 🍺 "
      "se conectar.</p>");
  client->println("<select name=\"ssid\">");
  client->println("<option value=\"0\">Escolha o Wi-Fi</option>");
  for (int i = 0; i < n; ++i) {
    client->print("<option value=\"");
    client->print(WiFi.SSID(i));
    client->print("\">");
    client->print(WiFi.SSID(i));
    client->println("</option>");
  }
  client->println("</select><br/>");
  client->println(
      "<input type=\"password\" name=\"password\" placeholder=\"Informe a "
      "senha\" /><br/>");
  client->println("<input type=\"submit\" value=\"Salvar\"><br/>");
  if (error) {
    client->println(
        "<div style=\"color: #e84118;\">Falha ao conectar no Wi-Fi</div>");
  }
  client->println("</form></body></html>");
  client->println();
}

void sendBodySuccess(WiFiClient* client, char* ssid) {
  client->println("<!DOCTYPE html><html lang=\"pt-br\">");
  client->println(
      "<head><meta charset=\"UTF-8\"><meta name=\"viewport\" "
      "content=\"width=device-width, initial-scale=1.0\">");
  client->println("<title>Successo - Cervejeira</title><style>");
  client->println("* { border: 0; margin: 0; padding: 0; }");
  client->println(
      "body { color: #fff; background: #535c68; width: 100vw; height: 100vh; "
      "display: flex; text-align: center; align-items: center; "
      "justify-content: center; }");
  client->println("</style></head><body><div>");
  client->println("<h1 style=\"margin-bottom: 10px;\">Wi-Fi Conectado ✔</h1>");
  client->print("<div>Rede ");
  client->print(ssid);
  client->println(
      ", conectada com sucesso.<br />Agora é só aproveitar sua "
      "cerveja gelada.</div>");
  client->println("</div></body></html>");
  client->println();
}