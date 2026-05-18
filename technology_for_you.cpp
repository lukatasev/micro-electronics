// Technology for you 2026 competition hosted by FEIT & Loging
// Mini piano consising of 5 notes (buttons), audio amplifier and LCD 16x2 display that writes what notes are played
// Pressing DO & SOL at the same time plays an automatic melody of exactly 6s
#include <LiquidCrystal.h>

const int RS = 7, EN = 8, D4 = 10, D5 = 11, D6 = 12, D7 = 13;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

const int btnK1 = 2; // DO
const int btnK2 = 3; // RE
const int btnK3 = 4; // MI
const int btnK4 = 5; // FA
const int btnK5 = 6; // SOL

const int audioPin = 9;

const int freqDO  = 262;
const int freqRE  = 294;
const int freqMI  = 330;
const int freqFA  = 349;
const int freqSOL = 392;
const int freqLA  = 440;

bool readyVisible = true;

void setup() {
  lcd.begin(16, 2);
  lcd.print("SYSTEM READY"); 
  
  pinMode(btnK1, INPUT);
  pinMode(btnK2, INPUT);
  pinMode(btnK3, INPUT);
  pinMode(btnK4, INPUT);
  pinMode(btnK5, INPUT);
}

void loop() {
  if (readyVisible && (digitalRead(btnK1) || digitalRead(btnK2) || 
      digitalRead(btnK3) || digitalRead(btnK4) || digitalRead(btnK5))) {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    readyVisible = false;
  }

  if (digitalRead(btnK1) == HIGH && digitalRead(btnK5) == HIGH) {
    runTieBreakerAutoplay();
  } 
  else if (digitalRead(btnK1) == HIGH) updatePiano("DO", freqDO);
  else if (digitalRead(btnK2) == HIGH) updatePiano("RE", freqRE);
  else if (digitalRead(btnK3) == HIGH) updatePiano("MI", freqMI);
  else if (digitalRead(btnK4) == HIGH) updatePiano("FA", freqFA);
  else if (digitalRead(btnK5) == HIGH) updatePiano("SOL", freqSOL);
  else {
    noTone(audioPin);
    lcd.setCursor(0, 1);
    lcd.print("                "); 
  }
}

void runTieBreakerAutoplay() {
  // DO DO SOL SOL LA LA SOL
  int melody[] = {freqDO, freqDO, freqSOL, freqSOL, freqLA, freqLA, freqSOL};
  String names[] = {"DO", "DO", "SOL", "SOL", "LA", "LA", "SOL"};
  
  // 6000ms / 7 notes
  int totalNotePeriod = 857; 
  int playTime = 730;    
  int gapTime = 127;   

  for (int i = 0; i < 7; i++) {
    lcd.setCursor(0, 1);
    lcd.print("NOTE: ");
    lcd.print(names[i]);
    lcd.print("     ");
    
    tone(audioPin, melody[i]);
    delay(playTime);
    noTone(audioPin);
    delay(gapTime);
  }
  
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void updatePiano(String noteName, int frequency) {
  tone(audioPin, frequency);
  lcd.setCursor(0, 1);
  lcd.print("NOTE: ");
  lcd.print(noteName);
  lcd.print("     ");
}
