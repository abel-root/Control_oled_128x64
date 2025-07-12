
# Communication avec un écran OLED 128x64 (ESP32)

Ce document décrit les étapes nécessaires pour configurer et utiliser un écran **OLED SSD1306** de taille **128x64** avec un microcontrôleur **ESP32** via le protocole **I2C**, en utilisant les bibliothèques **Adafruit_SSD1306** et **Adafruit_GFX**.

---

##  Prérequis

- Un écran OLED SSD1306 (résolution 128x64, interface I2C)
- Une carte ESP32
- Bibliothèques Arduino :
  - `Wire.h`
  - `Adafruit_SSD1306.h`
  - `Adafruit_GFX.h`

---

## Étape 1 : Inclusion des bibliothèques

```cpp
#include <Wire.h>                // Communication I2C
#include <Adafruit_GFX.h>        // Fonctions graphiques (dessin, texte, etc.)
#include <Adafruit_SSD1306.h>    // Contrôle de l'écran OLED
```
[Comprendre la bibliothèque Wire (I2C)](https://www.locoduino.org/spip.php?article77)


## Étape 2 : Définir les broches, l'adresse I2C et les dimensions de l'écran

```cpp
#define SDA_PIN        21         // Broche SDA de l'ESP32
#define SCL_PIN        22         // Broche SCL de l'ESP32
#define SCREEN_ADDRESS 0x3C       // Adresse I2C de l'écran OLED

#define SCREEN_WIDTH   128        // Largeur de l'écran OLED (en pixels)
#define SCREEN_HEIGHT  64         // Hauteur de l'écran OLED (en pixels)
#define OLED_RESET     -1         // Pas de broche de reset utilisée
```

### Création de l'objet `display`

```cpp
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
```

---

## Étape 3 : Initialisation dans `setup()`

```cpp
void setup() {
  Serial.begin(115200);                      // Initialisation de la liaison série
  Wire.begin(SDA_PIN, SCL_PIN);              // Initialisation du bus I2C (utile pour ESP32)

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Échec de l'initialisation de l'écran SSD1306"));
    while (true); // Boucle infinie en cas d'erreur
  }

  display.clearDisplay();                    // Nettoyer l'écran au démarrage
  display.display();
}
```

---

##  Étape 4 : Affichage dans `loop()`

```cpp
void loop() {
  display.clearDisplay();                    // Effacer l'écran
  display.setTextSize(2);                    // Définir la taille du texte
  display.setTextColor(SSD1306_WHITE);       // Définir la couleur (blanc sur noir)
  display.setCursor(0, 0);                   // Position du texte
  display.print("Bonjour le monde");         // Afficher le message
  display.display();                         // Rafraîchir l'écran
  delay(1000);                               // Pause d'une seconde
}
```

---

##  Taille du texte avec `setTextSize(n)`

| Taille (`n`) | Taille des caractères (px) | Caractères/lignes | Lignes affichables |
| ------------ | -------------------------- | ----------------- | ------------------ |
| 1            | 6 x 8                      | 21                | 8                  |
| 2            | 12 x 16                    | 10                | 4                  |
| 3            | 18 x 24                    | 7                 | 2                  |
| 4            | 24 x 32                    | 5                 | 2                  |

> Un caractère à `setTextSize(1)` fait 5 px + 1 px d'espacement → 6 px total de large

---

##  Positionnement avec `setCursor(x, y)`

* L’écran fait **128 x 64 pixels**
* `x` → position horizontale (0 à 127)
* `y` → position verticale (0 à 63)
* La grille change selon la taille du texte (`setTextSize(n)`)

### Exemple de repères (`setTextSize(1)`)

| Ligne | `y` en pixels | Description     |
|-------|----------------|-----------------|
| 0     | 0              | Haut de l’écran |
| 1     | 8              | Ligne 2         |
| 2     | 16             | Ligne 3         |
| 3     | 24             | Ligne 4         |
| 4     | 32             | Ligne 5         |
| 5     | 40             | Ligne 6         |
| 6     | 48             | Ligne 7         |
| 7     | 56             | Ligne 8         |


##  Exemple complet

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SDA_PIN        21
#define SCL_PIN        22
#define SCREEN_ADDRESS 0x3C

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  64
#define OLED_RESET     -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Échec de l'initialisation de l'écran SSD1306"));
    while (true);
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(12, 32);
  display.print("Hello!");
  display.display();
  delay(1000);
}
```

---

##  Ressources utiles

* [Documentation officielle Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
* [Exemples d’Adafruit GFX](https://learn.adafruit.com/adafruit-gfx-graphics-library/overview)
* [Article sur l'I2C avec Arduino (Locoduino)](https://www.locoduino.org/spip.php?article77)

---

##  Astuces

* Pour afficher plusieurs pages de texte ou dessiner des formes, explore les fonctions : `drawLine()`, `drawRect()`, `fillCircle()`, `drawBitmap()`...
* Utilise `display.clearDisplay()` avant d’écrire un nouveau contenu pour éviter les résidus.

---

##  Auteur

**Kouakou Abel Konan**
- [GitHub](https://github.com/abel-root)

```
