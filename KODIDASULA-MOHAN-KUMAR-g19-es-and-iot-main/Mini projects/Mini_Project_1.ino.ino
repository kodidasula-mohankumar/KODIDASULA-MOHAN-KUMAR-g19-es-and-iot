#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int leftButton = 2;
int rightButton = 5;
int ldr = A0;
int led = 4;
int buzzer = 3;
int threshold = 500; 
int position = 0;
int direction = 1;
bool previous = false;
unsigned long lastval = 0;
const unsigned long previousdelay = 200; 
byte happyface[8] = {
  B01010,  
  B01010,  
  B10001,  
  B01110 
};
int lastread[2] = {HIGH, HIGH};
int stablestate[2] = {HIGH, HIGH};
unsigned long lastdebounce[2] = {0, 0};
bool buttonPressed(int index, int pin) {
  int reading = digitalRead(pin);
  if (reading != lastread[index]) {
    lastdebounce[index] = millis();
    lastread[index] = reading;
  }
  if (millis() - lastdebounce[index] >= 20) {
    if (reading != stablestate[index]) {
      stablestate[index] = reading;
      if (stablestate[index] == LOW) {
        return true;
      }
    }
  }
  return false;
}
void showCharacter() {
  lcd.setCursor(0, 0);
  lcd.print("                "); 
  lcd.setCursor(position, 0);
  lcd.write(byte(0));           
}
void automaticSignal() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer,HIGH);
    delay(500);
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    delay(60); 
  }
}
void setup() {
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, happyface);
  lcd.setCursor(0, 0);
  lcd.print("MINI PROJECT 1");
  delay(800);
  lcd.clear();
  showCharacter();
}
void loop() {
  int lightValue = analogRead(ldr);
  bool autoMode = (lightValue >= threshold);
 if (autoMode != previous) {
    previous= autoMode;    
    lcd.setCursor(0, 1);
    if (autoMode) {
      lcd.print("AUTO   ");
      showCharacter();
      automaticSignal(); 
      lastval = millis();
    } else {
      lcd.print("MANUAL   ");
      showCharacter();
    }
  }
  if (autoMode) {
    if (millis() - lastval >= previousdelay) {
      lastval = millis();
      position += direction;
      if (position >= 15) {
        position = 15;
        direction = -1;
      }
      if (position <= 0) {
        position = 0;
        direction = 1;
      }
      showCharacter();
    }
  } else {
        if (buttonPressed(0, leftButton)) {
      if (position > 0) {
        position--;
        showCharacter();
      }
    }
    if (buttonPressed(1, rightButton)) {
      if (position < 15) {
        position++;
        showCharacter();
      }
    }
  }
}