#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON1_PIN D5  // Yes
#define BUTTON2_PIN D7  // No

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 250;

struct StoryNode {
  const char* text;
  int yes;
  int no;
};

StoryNode story[] = {
  {"Andrea wakes up.\nIs she Eepy?", 1, 2},
  {"She Eepy.\nStay in bed?", 3, 4},
  {"Not Eepy.\nGet matcha?", 5, 6},
  {"Rudy cuddles.\nTake a nap?", 7, 8},
  {"Rudy angry now.\nApologize?", 9, 10},
  {"David joins.\nGet sushi?", 11, 12},
  {"Work at GFT.\nSend meme to David?", 13, 14},
  {"Dreams of hotpot.\nWake up hungry?", 15, 16},
  {"You stare at wall.\nArt?", 17, 18},
  {"Rudy forgives you.\nVictory nap?", 19, 20},
  {"Rudy becomes CEO.\nYou now intern.", -1, -1},
  {"Andrea eats 14 rolls.\nRegret?", 21, 22},
  {"Sushi skipped.\nDavid sad.", -1, -1},
  {"David replies:\n'Cringe.'", 23, 24},
  {"You do work things.\nYay productivity!", -1, -1},
  {"You wake up.\nPepper plant talking?", 25, 26},
  {"Still dreaming.\nAHS style now.", -1, -1},
  {"You paint Rudy.\nIt's cursed?", 27, 28},
  {"Wall stares back.\nYou okay?", -1, -1},
  {"Nap complete.\nFeeling brave?", 5, 29},
  {"Rudy steals socks.\nClassic.", -1, -1},
  {"David feeds you\nspicy pepper.", 30, 31},
  {"You eat more.\nDavid impressed.", -1, -1},
  {"He sends 7 memes.\nOne hits.", -1, -1},
  {"GFT replies LOL.\nYou win meme war.", -1, -1},
  {"'I'm ghost pepper.'\nChallenge accepted?", 21, 22},
  {"No ghost pepper.\nBut Rudy blinks.", -1, -1},
  {"Rudy now cursed.\nMust burn painting.", -1, -1},
  {"Rudy immortalized.\nGallery wants it.", -1, -1},
  {"Nap becomes eternal.\nDavid joins too.", -1, -1},
  {"David says:\n'I love you <3 (WIN!)'", -1, -1}
};

int currentIndex = 0;
bool showingEnd = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  Wire.begin(D2, D1);

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
  delay(1500);

  displayStory();
}

void loop() {
  if (millis() - lastDebounceTime < debounceDelay) return;

  if (digitalRead(BUTTON1_PIN) == LOW) {
    lastDebounceTime = millis();
    Serial.println("Yes (Button 1)");
    handleChoice(true);
  }

  if (digitalRead(BUTTON2_PIN) == LOW) {
    lastDebounceTime = millis();
    Serial.println("No (Button 2)");
    handleChoice(false);
  }
}

void handleChoice(bool isYes) {
  if (showingEnd) {
    currentIndex = 0;
    showingEnd = false;
    displayStory();
    return;
  }

  int next = isYes ? story[currentIndex].yes : story[currentIndex].no;
  if (next == -1) {
    displayMessage("The End \n(Press any btn)");
    showingEnd = true;
  } else {
    currentIndex = next;
    displayStory();
  }
}

void displayStory() {
  displayMessage(story[currentIndex].text);
}

void displayMessage(const char* msg) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(msg);
  display.display();
}