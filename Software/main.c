#include <LiquidCrystal.h>
#include "tinyexpr.h"

const int rs = 6, en = 7, d4 = 2, d5 = 3, d6 = 4, d7 = 5;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {:

  lcd.begin(16, 2);

  lcd.print("EB3 Calculator");
  lcd.setCursor(0, 1);
  lcd.print("By: Evan Gubarev");
  delay(3000);
  lcd.clear();
  lcd.print("Press any key.");

  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);



  Serial.begin(9600);
  Serial.println("Connection started");
  Serial.println(A0);
  Serial.println(PC0);
  Serial.println(PB0);
}

String eq = "";
String result = "";
const char layout[5][4] = { { 'a','^','(',')' }, { '7','8','9','/' }, { '4','5','6','*' }, { '1','2','3','-' }, { 'r','0','.','+' } };
char lastKeyPress = '\0';
int lastA = -1;


void loop() {

  int a=-1, b=-1;

  char charPressed;
  for (int i=0; i<4; i++) {
    pinMode(8+i, OUTPUT);
    digitalWrite(8+i, LOW);
    for (int j=0; j<5; j++) {
        if (digitalRead(14 + j) == LOW) {
          Serial.print(i);
          Serial.print(' ');
          Serial.println(j);
          a = i;
          b = j;
          break;
        }
    }
    if (lastA == i && b==-1) lastKeyPress = '\0';
    pinMode(8+i, INPUT_PULLUP);
  }


  delay(50);


  if (a==-1 || b==-1) return;

  char key = layout[b][a];
  if (lastKeyPress == key) return;
  lcd.clear();

  if (key != 'r' && key != 'a' && key != 's' && key != 'd' && key != 'f' ) {
  eq += (key);
  } else if (key == 'r') {
    eq.remove(eq.length()-1);
  } else if (key == 'a') {
    eq = "";
  }
  lastKeyPress = key;
  lastA = a;


  lcd.setCursor(0, 0);
  lcd.print(eq);
  lcd.setCursor(0, 1);
  int error;
  double result = te_interp(eq.c_str(), &error);
  if (error == 0) lcd.print(result);


}
