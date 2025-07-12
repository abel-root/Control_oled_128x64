Ce document permet de ddefinir les étapes de communication avec un écran oled de taille 128x64

# Etape 1 : Inclusion de bibliothèque
Pour commencer, il faut inclure les bibliothèques néccessaire comme :
1. ``Wire.h`` : cette bibliothèque permet de configurer la communication `I2C`
>` https://www.locoduino.org/spip.php?article77` Lien pour mieux comprendre comment functionne cette bibliothèque
2. ` Adafruit_SSD1306.h` // librairy qui permet de communiquer avec l'écran `OLED` et aussi, 
    `Adafruit_GFX.h` // pour desiner sur l'écran
# Etape 2 : Définition des pins I2C et Adresse de l'esclave(``oled``) et sa taille
1. `#define SDA_PIN 21` // permet de définir la broche SDA de l'esp32 pour la transmission des données
2. `#define SCL_PIN 22 ` // permet de définir la broche SCL de l'esp32 pour l'horloge
3. `#define SCREEN_ADDRESS 0x3C` // Adresse de l'esclave

## Taille de l'écran `OLED`

1. `#define SCREEN_WIDTH 128` // Largeur de l'écran OLED en pixels
2. `#define SCREEN_HEIGHT 64` // Hauteur de l'écran OLED en pixels
3. `#define OLED_RESET     -1` /1

## Créer un objet de `Adafruit_SSD1306`

`Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);` // `display` est un objet de `Adafruit_SSD1306`, le constructeur prend en paramètre , la taille de l'écran : `longeur` (SCREEN_WIDTH) et `largeur` (SCREEN_HEIGHT), l'adresse de l' objet de la classe Wire (&Wire) et de reset de l'OLED (OLED_RESET). 

# Etape 3 : Dans setup( )

 1. `Serial.begin(115200)` // Initialiser le port série en `115200` qui est la vitesse de transmission. 
 2. `Wire.begin(SDA_PIN, SCL_PIN)`  // Initialiser I2C si nécessaire (utile pour ESP32)
    
3.   Initialisation de l'écran  
```bash 
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Échec de l'initialisation de l'écran SSD1306"));
    while (true); // Boucle infinie en cas d'erreur
  }
```  
# Etape 4 : Dans loop()

Définir le corps de ton programme ici et pransmettre les données à l'écran :

```bash

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Bonjour le monde");
  display.display();
  delay(1000);

```
  
## Taille du texte (`setTextSize(n)`) sur écran OLED SSD1306 (128x64)

| `setTextSize(n)` | Taille caractères (px) | Nb. max de caractères par ligne | Nb. max de lignes |
|------------------|-------------------------|----------------------------------|-------------------|
| 1                | 6 x 8                   | 21                               | 8                 |
| 2                | 12 x 16                 | 10                               | 4                 |
| 3                | 18 x 24                 | 7                                | 2                 |
| 4                | 24 x 32                 | 5                                | 2                 |

> Largeur d’un caractère à `setTextSize(1)` = 5 pixels + 1 pixel d’espace = 6 px

---

## 🎯 Position du curseur (`setCursor(x, y)`)

- 📏 L’écran mesure **128 x 64 pixels**
- `x` = position horizontale en pixels (0 → 127)
- `y` = position verticale en pixels (0 → 63)
- La grille change selon `setTextSize()`

### ➤ Repères à `setTextSize(1)` :
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

---

## ✅ Exemple

```cpp
display.setTextSize(2);
display.setCursor(12, 32);
display.print("Hello!");
display.display();
