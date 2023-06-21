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

// Variáveis globais
bool iniciarPrograma = false;

void drawHomeScreen()
{
  // TITULO "MENU PRINCIPAL"
  tft.setTextSize(3); 
  tft.setTextColor(BLACK);

  // RETANGULO DO TITULO
  tft.fillRect(20, 20, 440, 30, BLUE);
  
  // ALINHA E IMPRIME NO DISPLAY "MENU PRINCIPAL" 
  int16_t textWidth, textHeight;
  tft.getTextBounds("MENU PRINCIPAL", 0, 0, nullptr, nullptr, &textWidth, &textHeight);

  int16_t textX = (tft.width() - textWidth) / 2; // Centraliza o texto horizontalmente
  int16_t textY = 25; // Posição vertical do texto

  tft.setCursor(textX, textY);
  tft.print("MENU PRINCIPAL");
  //-------------------------------


  //-------------------------------

  int screenWidth = tft.width();
  int screenHeight = tft.height();
  int buttonWidth = 160;
  int buttonHeight = 70;
  int buttonX = (screenWidth - buttonWidth) / 2;
  int buttonY = (screenHeight - buttonHeight) / 2 - 50;

  // BUTÃO INCIAR PROGRAMA / ENCERRAR PROGRAMA
  tft.fillRoundRect(buttonX, buttonY, buttonWidth, buttonHeight, 5, DARKER_GREEN);
  tft.drawRoundRect(buttonX, buttonY, buttonWidth, buttonHeight, 5, WHITE);
  tft.setTextColor(BLACK); // Define a cor do texto para branco
  tft.setTextSize(3); // Define o tamanho do texto para 3
  tft.setCursor(buttonX + (buttonWidth - 30) / 4 - 17, buttonY + (buttonHeight - textHeight) / 2);
  tft.println("INICIAR"); // Escreve o texto no botão

  // BOTÃO AJUSTAR VALVULAS
  int ajustesButtonY = buttonY + buttonHeight + 20;
  tft.fillRoundRect(buttonX, ajustesButtonY, buttonWidth, buttonHeight, 5, BLUE);
  tft.drawRoundRect(buttonX, ajustesButtonY, buttonWidth, buttonHeight, 5, WHITE);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(buttonX + (buttonWidth - 50) / 4 - 17, ajustesButtonY + (buttonHeight - 8) / 3 + 5);
  tft.println("VALVULAS");

  // Informação das válvulas ativas
  int valveInfoWidth = 80;
  int valveInfoHeight = 30;
  int valveInfoX = tft.width() - valveInfoWidth - 10; // Posição X 
  int valveInfoY = 280; // Posição Y 

  tft.fillRoundRect(valveInfoX, valveInfoY, valveInfoWidth, valveInfoHeight, 5, BLUE);
  tft.drawRoundRect(valveInfoX, valveInfoY, valveInfoWidth, valveInfoHeight, 5, WHITE);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(407, 287);
  tft.println("V: 0");
}

void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  Waveshield.begin();
  tft.fillScreen(BLACK);
  tft.setRotation(3);
  drawHomeScreen();

}

int buttonWidth2 = 200;
int buttonHeight2 = 50;
int buttonX2 = (tft.width() - buttonWidth2) / 2;
int buttonY2 = (tft.height() - buttonHeight2) / 2 - 60;

void loop() 
{
  TSPoint p = Waveshield.getPoint();

  p.x = tft.width() - (map(p.x, 0, 480, tft.width(), 0));
  p.y = tft.height() - (map(p.y, 0, 320, tft.height(), 0));

  // Serial.print(p.x);
  // Serial.print("    ");
  // Serial.print(p.y);
  // Serial.print("    ");
  // Serial.print(p.z);
  // Serial.println("");

  // Verifica se o toque ocorreu dentro dos limites do botão INICIAR
  if (p.x > buttonX2 && p.x < buttonX2 + buttonWidth2 && p.y > buttonY2 && p.y < buttonY2 + buttonHeight2)
  {
    Serial.print("TOCOU");
  }
}

