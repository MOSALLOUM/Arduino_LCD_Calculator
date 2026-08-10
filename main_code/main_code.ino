#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

const byte rows = 4;
const byte cols = 4;

char hexakeys[rows][cols] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

byte rowpins[rows] = {2,3,4,5};
byte colpins[cols] = {6,7,8,9};

Keypad customKeypad = Keypad(makeKeymap(hexakeys), rowpins, colpins, rows, cols); 

String num1 = "";
String num2 = "";

long number = 0;
int count = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  num1 = "";
  count = 0;
  number = 0;
  
  char c = customKeypad.getKey();
  while(c == NO_KEY) {
    c = customKeypad.getKey();
  }

  while(c >= '0' && c <= '9') {
    num1 += c;
    Serial.println(num1);
    c = customKeypad.getKey();
    while(c == NO_KEY) {
      c = customKeypad.getKey();
    }
  }

  int i = 0;
  while(num1[i] != '\0') {
    number = (number * 10) + (num1[i] - '0');
    i++;
  }
  
}

