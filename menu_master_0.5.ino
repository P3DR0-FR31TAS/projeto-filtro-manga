#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Waveshare4InchTftShield.h>

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

namespace
{
  Waveshare4InchTftShield Waveshield;
  Adafruit_GFX &tft = Waveshield;
}

void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  Waveshield.begin();
  tft.fillScreen(WHITE);
  tft.setRotation(3);
  tft.fillRoundRect(200, 50, 40, 40, 3, GREEN);
  tft.setTextColor(WHITE); // Define a cor do texto para branco
  tft.setTextSize(1); // Define o tamanho do texto para 2
  tft.setCursor(205, 60); // Define a posição do texto dentro do botão
  tft.println("Botao"); // Escreve o texto no botão

}

void loop() {
  // put your main code here, to run repeatedly:
}
