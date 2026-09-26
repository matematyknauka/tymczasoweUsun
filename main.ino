#include "moje_lcd.h"

void setup() {
  set_up();
  // Wyświetlanie tekstów
    setCursor(3, 0);
    printLCD("Godzina");

    setCursor(0, 1);
    char buffer[16];
    sprintf(buffer, "%02d:%02d", 2, 54);
    printLCD(buffer);
}

void loop() {

}
