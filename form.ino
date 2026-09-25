#include "Arduino.h"
#include "Audio.h"
#include <WebServer.h>
#include <WiFi.h>

    #define I2S_DOUT      25
    #define I2S_BCLK      27
    #define I2S_LRC       26
    int VOLUME = 21;
    String ADDRESS = "http://62.133.128.18:8040/listen.pls";
#define WIFI_SSID "multimedia_Cegielnia18"
#define WIFI_PASSWORD "Cegieldanci91"

Audio audio;

void audio_info(const char* info) {
    Serial.printf("%s\n", info);
}

WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Połączenie z siecią Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.print("Adres IP serwera: ");
  Serial.println(WiFi.localIP());

  // Definicja strony głównej (ścieżka "/")
  server.on("/", []() {
    // Sprawdzamy, czy użytkownik wysłał tekst w formularzu (pole "newVolume")
    if (server.hasArg("newVolume")) {
      VOLUME = server.arg("newVolume").toInt(); // Zapamiętujemy nową wartość
    }

    // Budujemy stronę HTML z aktualną wartością i formularzem
    String html = "<h1>Glosnosc: " + String(VOLUME) + "</h1>";
    html += "<form action='/' method='GET'>";
    html += "<input type='text' name='newVolume' placeholder='Wpisz wartosc'>";
    html += "<input type='submit' value='Zapisz'>";
    html += "</form>";
    server.send(200, "text/html", html); // Wysyłamy stronę do przeglądarki
  });

  // Uruchomienie serwera
  server.begin();

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(VOLUME); // default 0...21
  audio.connecttohost(ADDRESS.c_str());
}

void loop() {
  // Obsługa przychodzących połączeń
  server.handleClient();
  audio.loop();
  vTaskDelay(1);
}
