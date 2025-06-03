#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON1_PIN D5
#define BUTTON2_PIN D7

void setup() {
  Serial.begin(115200);
  
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  
  Wire.begin(D2,D1);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
   display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Wide OLED Ready!");
  display.display();

}

void loop() {
  if (digitalRead(BUTTON1_PIN) == LOW) {
    Serial.println("B1");
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Button 1 Pressed");
    display.display();
    delay(300);  // Debounce
  }

  if (digitalRead(BUTTON2_PIN) == LOW) {
    Serial.println("B2");
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Button 2 Pressed");
    display.display();
    delay(300);  // Debounce
  }

  // Serial.println(String("B1 ") + digitalRead(BUTTON1_PIN));
  // Serial.println(String("B2 ") + digitalRead(BUTTON2_PIN));
  // delay(100);

}
