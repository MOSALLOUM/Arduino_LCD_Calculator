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

LiquidCrystal_I2C lcd(0x27, 16, 2);

String num1 = "";
String num2 = "";

long number1 = 0;
long number2 = 0;
int count = 0;
int column_counter_1 = 0;
int column_counter_2 = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME!");
  delay(3000);
  lcd.clear();
}

void loop() {
  
  num1 = "";
  num2 = "";
  count = 0;
  number1 = 0;
  number2 = 0;
  column_counter_1 = 0;
  column_counter_2 = 0;
  
  char c = customKeypad.getKey();
  while(c == NO_KEY) {
    c = customKeypad.getKey();
  }

  lcd.setCursor(0,0);
  while(c >= '0' && c <= '9') {
    num1 += c;
    lcd.print(num1);
    column_counter_1++;
    c = customKeypad.getKey();
    while(c == NO_KEY) {
      c = customKeypad.getKey();
    }
    lcd.setCursor(0, 0);
  }

  int i = 0;
  while(num1[i] != '\0') {
    number1 = (number1 * 10) + (num1[i] - '0');
    i++;
  }

  lcd.setCursor(column_counter_1, 0);
  lcd.print(c);


  char d = customKeypad.getKey();
  while(d == NO_KEY) {
    d = customKeypad.getKey();
  }

  lcd.setCursor(0, 1);
  while(d >= '0' && d <= '9') {
    num2 += d;
    lcd.print(num2);
    column_counter_2++;
    d = customKeypad.getKey();
    while(d == NO_KEY) {
      d = customKeypad.getKey();
    }
    lcd.setCursor(0, 1);
  }

  int j = 0;
  while(num2[j] != '\0') {
    number2 = (number2*10)+(num2[j] - '0');
    j++;
  }

  
  
}

