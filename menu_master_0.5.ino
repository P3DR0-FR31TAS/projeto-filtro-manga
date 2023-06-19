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
#define DARKER_GREEN 0x0706

namespace
{
  Waveshare4InchTftShield Waveshield;
  Adafruit_GFX &tft = Waveshield;
}

void drawHomeScreen()
{
  tft.setTextSize(3);
  tft.setTextColor(BLUE);

  // ALINHA E IMPRIME "MENU PRINCIPAL" 
  int16_t textWidth, textHeight;
  tft.getTextBounds("MENU PRINCIPAL", 0, 0, nullptr, nullptr, &textWidth, &textHeight);

  int16_t textX = (tft.width() - textWidth) / 2; // Centraliza o texto horizontalmente
  int16_t textY = 15; // Posição vertical do texto

  tft.setCursor(textX, textY);
  tft.print("MENU PRINCIPAL");
  //-------------------------------

  // LINHA HORIZONTAL
  int16_t x = 0;       // coordenada x do ponto inicial
  int16_t y = 50;      // coordenada y do ponto inicial
  int16_t width = 480;  // largura da linha
  int16_t thickness = 3; // espessura da linha
  uint16_t color = BLUE; // cor da linha

  for (int16_t i = 0; i < thickness; i++) {
    tft.drawFastHLine(x, y + i, width, color);
  }
  //-------------------------------

  int buttonWidth = 200;
  int buttonHeight = 50;
  int screenWidth = tft.width();
  int screenHeight = tft.height();
  int buttonX = (screenWidth - buttonWidth) / 2;
  int buttonY = (screenHeight - buttonHeight) / 2 - 60;

  // BUTÃO INCIAR PROGRAMA / ENCERRAR PROGRAMA
  tft.fillRoundRect(buttonX, buttonY, buttonWidth, buttonHeight, 10, DARKER_GREEN);
  tft.setTextColor(WHITE); // Define a cor do texto para branco
  tft.setTextSize(3); // Define o tamanho do texto para 3
  tft.setCursor(buttonX + (buttonWidth - 30) / 4, buttonY + (buttonHeight - textHeight) / 2);
  tft.println("INICIAR"); // Escreve o texto no botão

  // BOTÃO AJUSTAR VALVULAS
  int ajustesButtonY = buttonY + buttonHeight + 20;
  tft.fillRoundRect(buttonX, ajustesButtonY, buttonWidth, buttonHeight, 10, BLUE);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(buttonX + (buttonWidth - 50) / 4, ajustesButtonY + (buttonHeight - 8) / 3);
  tft.println("VALVULAS");

  // Informação das válvulas ativas
  int valveInfoWidth = 80;
  int valveInfoHeight = 30;
  int valveInfoX = tft.width() - valveInfoWidth - 10; // Posição X 
  int valveInfoY = 280; // Posição Y 
  int valveInfoSpacing = 5; // Espaçamento entre os retângulos das válvulas ativas

  tft.fillRoundRect(valveInfoX, valveInfoY, valveInfoWidth, valveInfoHeight, 5, GREEN);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(valveInfoX + valveInfoHeight + valveInfoSpacing, valveInfoY + valveInfoHeight / 2);
  tft.println("VALVULA: 0");
}

void setup() 
{
  SPI.begin();
  Waveshield.begin();
  tft.fillScreen(BLACK);
  tft.setRotation(3);

  drawHomeScreen();
}

void loop() 
{
  
}
