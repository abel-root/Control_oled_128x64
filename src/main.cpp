#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SDA_PIN 21  // Broche SDA de l'écran OLED (pour ESP32)
#define SCL_PIN 22  // Broche SCL de l'écran OLED (pour ESP32)
#define SCREEN_ADDRESS 0x3C

#define SCREEN_WIDTH 128 // Largeur de l'écran OLED en pixels
#define SCREEN_HEIGHT 64 // Hauteur de l'écran OLED en pixels
#define OLED_RESET     -1 // Reset non utilisé (partagé avec reset Arduino)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
// Image deux yeux 32x16 pixels


void setup() {
  Serial.begin(115200);

  // Initialiser I2C si nécessaire (utile pour ESP32)
  Wire.begin(SDA_PIN, SCL_PIN);  

  // Initialiser l'écran
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Échec de l'initialisation de l'écran SSD1306"));
    while (true); // Boucle infinie en cas d'erreur
  }

  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(28, 4);
  display.print("Salut on va compter jusqu'à 100.");
  display.display();

}

void loop() {

  for (int i = 0; i < 200; i++) {
    display.clearDisplay();               // Efface l’écran à chaque tour
    
    display.setTextSize(1); // size of the title

    display.setTextColor(SSD1306_WHITE); // couleur des textes 

    // __entête__
    display.setCursor(50, 0);  // position du cruseur 
    display.print("INT ");
    display.setCursor(50,35);  // position du cruseur 
    display.print("HEX");


    // __Valeur__
    display.setTextSize(2); // Size of the text 

    display.setCursor(48, 13);            
    display.print(i);                    

    display.setCursor(45, 48);           
    display.print("0x");
    display.print(i, HEX);
          

    display.display();                   // Met à jour l’écran

    delay(1000);                           // Pause pour voir le compteur
  }

}
