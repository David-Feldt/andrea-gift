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
  {"NYE snow falling.\nLeave house?", 1, 2},
  {"Party invite open.\nWear Snoopy fit?", 3, 4},
  {"Snorlax blocks door.\nWake him?", 5, 6},
  {"Snoopy fit ready.\nHead out?", 7, 8},
  {"Outfit feels wrong.\nChange clothes?", 8, 9},
  {"Snorlax grumbles.\nOffer snacks?", 10, 6},
  {"Snorlax unmoved.\nStay home?", 11, 12},
  {"Driving in snow.\nSpeed up?", 13, 14},
  {"Running late.\nRush anyway?", 7, 11},
  {"You change outfits.\nMiss party?", 11, 7},
  {"Snorlax moves.\nLeave now?", 7, 11},
  {"Home alone.\nPlan Cuba trip?", 15, 16},
  {"Couch looks comfy.\nTake nap?", 17, 18},
  {"Red light ahead.\nRun it?", 19, 20},
  {"Careful driving.\nArrive late?", 21, 22},
  {"Cheap flights found.\nBook Cuba?", 23, 16},
  {"Trip feels risky.\nCancel search?", 11, 24},
  {"You fall asleep.\nOversleep?", 25, 26},
  {"You stay awake.\nGo party?", 7, 11},
  {"Sirens flash.\nPull over?", 27, 28},
  {"You slow down.\nKeep driving?", 21, 27},
  {"You reach party.\nGo inside?", 29, 30},
  {"Party nearly over.\nStill enter?", 29, 31},
  {"Cuba trip booked.\nWIN", -1, -1},
  {"Plans abandoned.\nLOSE", -1, -1},
  {"You oversleep.\nLOSE", -1, -1},
  {"Nap ends.\nResetting night.", 0, -1},
  {"Officer warns you.\nDrive home?", 11, 21},
  {"Ticket issued.\nLOSE", -1, -1},
  {"Music loud inside.\nFind David?", 32, 33},
  {"Andrea alone.\nLeave party?", 11, 34},
  {"Lights shutting down.\nLOSE", -1, -1},
  {"Pranav grabs David.\nStop him?", 35, 36},
  {"David eating sketchy food.\nWarn him?", 37, 38},
  {"Friends fully flake.\nLOSE", -1, -1},
  {"You pull David back.\nStay together?", 33, 30},
  {"Pranav escapes.\nLOSE", -1, -1},
  {"David ignores you.\nInsist harder?", 39, 38},
  {"Food poisoning hits.\nLOSE", -1, -1},
  {"David listens.\nCrisis avoided?", 29, 30},
  {"Hospital visit ends.\nLOSE", -1, -1}
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