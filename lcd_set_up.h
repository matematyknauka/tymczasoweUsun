Wire.begin();
    delay(50);

    // Sekwencja inicjalizacji HD44780 w trybie 4-bitowym
    lcd_send(0x33, 0);
    delay(5);
    lcd_send(0x32, 0);
    delay(5);
    
    // Konfiguracja pracy
    lcd_send(0x28, 0); // 4-bit, 2 linie, font 5x8
    lcd_send(0x0C, 0); // Ekran włączony, kursor wyłączony
    lcd_send(0x06, 0); // Inkrementacja kursora
    clearLCD();
