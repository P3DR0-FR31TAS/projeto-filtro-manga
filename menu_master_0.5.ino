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

int screenWidth;
int screenHeight;
int buttonWidth;
int buttonHeight;
int buttonX;
int buttonY;

// Variáveis de debounce
bool buttonState = false;

void drawHomeScreen()
{
  // DEFINE O TAMAHO E COR DO TITULO
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

  screenWidth = tft.width();
  screenHeight = tft.height();
  buttonWidth = 160;
  buttonHeight = 70;
  buttonX = (screenWidth - buttonWidth) / 2;
  buttonY = (screenHeight - buttonHeight) / 2 - 50;

  // BUTÃO INCIAR PROGRAMA 
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

  screenWidth = tft.width();
  screenHeight = tft.height();
  buttonWidth = 160;
  buttonHeight = 70;
  buttonX = (screenWidth - buttonWidth) / 2;
  buttonY = (screenHeight - buttonHeight) / 2 - 50;
}

// int buttonWidth2 = 160;
// int buttonHeight2 = 70;
// int buttonX2 = (tft.width() - buttonWidth2) / 2;
// int buttonY2 = (tft.height() - buttonHeight2) / 2 - 50;

void loop() 
{
  TSPoint p = Waveshield.getPoint();
  Waveshield.normalizeTsPoint(p);

  // Verifica se o toque ocorreu dentro dos limites do botão INICIAR
  if (p.z > 10 && p.x > 160 && p.x < 330 && p.y > 70 && p.y < 140)
  {
    // Verifique se o botão estava pressionado anteriormente
    if (!buttonState)
    {
      // Atualize o estado do botão
      buttonState = true;

      // Ação quando o botão é pressionado
      iniciarPrograma = !iniciarPrograma;
      Serial.println(iniciarPrograma);

      // Altere a cor e o texto do botão
      if (iniciarPrograma)
      {
        // BUTÃO INCIAR PROGRAMA 
        tft.fillRoundRect(buttonX, buttonY, buttonWidth, buttonHeight, 5, RED);
        tft.drawRoundRect(buttonX, buttonY, buttonWidth, buttonHeight, 5, WHITE);
        tft.setTextColor(BLACK); // Define a cor do texto para branco
        tft.setTextSize(3); // Define o tamanho do texto para 3
        tft.setCursor(170, 90);
        tft.println("ENCERRAR"); // Escreve o texto no botão
      }
      else
      {
        // BUTÃO INCIAR PROGRAMA 
        tft.fillRoundRect(buttonX, buttonY, buttonWidth, buttonHeight, 5, DARKER_GREEN);
        tft.drawRoundRect(buttonX, buttonY, buttonWidth, buttonHeight, 5, WHITE);
        tft.setTextColor(BLACK); // Define a cor do texto para branco
        tft.setTextSize(3); // Define o tamanho do texto para 3
        tft.setCursor(170, 90);
        tft.println("INICIAR"); // Escreve o texto no botão
      }
    }
  }
  else
  {
    // Verifique se o estado do botão mudou
    if (buttonState)
    {
      // Atualize o estado do botão
      buttonState = false;

      // Ação quando o botão é liberado
    }
  }
}

