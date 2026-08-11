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
  lcd.clear();
  
  char c = customKeypad.getKey();
  while(c == NO_KEY) {
    c = customKeypad.getKey();
  }

  lcd.setCursor(0,0);
  while(c >= '0' && c <= '9') {

    if(num1.length() >= 10) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TOO LONG!");
      return;
    }

    num1 += c;
    lcd.print(c);
    column_counter_1++;
    c = customKeypad.getKey();
    while(c == NO_KEY) {
      c = customKeypad.getKey();
    }
    lcd.setCursor(num1.length(), 0);
  }

  if(c=='C') return;

  int i = 0;
  while(num1[i] != '\0') {
    number1 = (number1 * 10) + (num1[i] - '0');
    i++;
  }

  lcd.setCursor(num1.length(), 0);
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
    lcd.setCursor(num2.length(), 1);
  }

  int j = 0;
  while(num2[j] != '\0') {
    number2 = (number2*10)+(num2[j] - '0');
    j++;
  }

  if(d == 'C') return;

  float answer;
  switch(c) {
    case '+':
      answer = number1 + number2;
    break;

    case '-':
      answer = number1-number2;
    break;

    case '*':
      answer = number1 * number2;
    break;

    case '/':
      if(number2 == 0) return;
      number1 = (float)number1;
      number2 = (float)number2;
      answer = (number1/number2);
    break;

    case 'C':
      return;
    break;

    default: 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No such op");
      return;
  }

  d = customKeypad.getKey();
  while(d == NO_KEY) {
    d = customKeypad.getKey();
  }

  if(d == '='){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Answer: ");
    lcd.setCursor(0, 1);
    lcd.print(answer);
    delay(5000);
  }

  
  
}

