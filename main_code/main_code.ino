#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

//Rows and Columns of your matrix

const byte rows = 4;
const byte cols = 4;

//The mapping you want of the matrix. You can change these around however you like.

char hexakeys[rows][cols] = {
  {'1', '2', '3', '+'}, // + : addition
  {'4', '5', '6', '-'}, // - : subtraction
  {'7', '8', '9', '*'}, // * : multiplication
  {'C', '0', '=', '/'}  // C : clear ; / : division
};                      //Your keypad will probably have different keys but you can use whatever.

//Setting the GPIOS.

byte rowpins[rows] = {2,3,4,5};
byte colpins[cols] = {6,7,8,9};

//Making the keypad instance.

Keypad customKeypad = Keypad(makeKeymap(hexakeys), rowpins, colpins, rows, cols); 

//LCD instance.

LiquidCrystal_I2C lcd(0x27, 16, 2);

//Strings to store in the incoming input.

String num1 = "";
String num2 = "";

long number1 = 0;
long number2 = 0;
int count = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor(0,1);
  lcd.print(" Arduino Calc. ");
  delay(3000);
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
  
  //Resetting variables for next itiration.
  num1 = "";
  num2 = "";
  count = 0;
  number1 = 0;
  number2 = 0;
  lcd.clear();
  
  //Keeps the arduino checking whether a character has been input or not.
  char c = customKeypad.getKey();
  while(c == NO_KEY) {
    c = customKeypad.getKey();
  }

  //Main input loop, receives the first operand.
  lcd.setCursor(0,0);
  while(c >= '0' && c <= '9') {

    //Since the data type we're using (long) can store up to 2,147,483,647 which is 10 digits.
    //This will also affect your results
    if(num1.length() >= 10) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TOO LONG!");
      return;
    }
    
    //Adds the recived input from the keypad to the string and prints it on the screen.
    num1 += c;
    lcd.print(c);
    c = customKeypad.getKey();
    while(c == NO_KEY) {
      c = customKeypad.getKey();
    }
  }

  //C is for clear, so we reset the code.
  if(c=='C') return;

  int i = 0;
  while(num1[i] != '\0') {
    number1 = (number1 * 10) + (num1[i] - '0');
    i++;
  }

  lcd.setCursor(num1.length(), 0);
  lcd.print(c);

  //In case the user clicked equal with no operator.

  if(c=='=') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Answer: ");
    lcd.setCursor(0, 1);
    lcd.print(number1);
    delay(5000);
  }

  //Input second number.

  char d = customKeypad.getKey();
  while(d == NO_KEY) {
    d = customKeypad.getKey();
  }

  lcd.setCursor(0, 1);
  while(d >= '0' && d <= '9') {
    if(num2.length() >= 10) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TOO LONG!");
      return;
    }
    num2 += d;
    lcd.print(d);
    d = customKeypad.getKey();
    while(d == NO_KEY) {
      d = customKeypad.getKey();
    }
  }

  //C is for clear, so we reset the code.
  if(d == 'C') return;

  //Main conversion loop; converts the string into long.
  //You can use the .toInt() with the string, but I preffered to use a more manual method. 
  int j = 0;
  while(num2[j] != '\0') {
    number2 = (number2*10)+(num2[j] - '0');
    j++;
  }

  //Setup the operations.
  double answer;
  switch(c) {
    case '+':
      answer = number1 + number2;
    break;

    case '-':
      answer = number1-number2;
    break;

    case '*':
      answer = (float)number1 * (float)number2;
      Serial.println(answer);
    break;

    case '/':
      if(number2 == 0) return; //You can add a warning or an error message.
      answer = (float)number1/number2;
    break;

    case 'C':
      return;

    default: 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No such op");
      return;
  }

  //Only displays answer after clicking '=', otherwise resets the code.
  //And d already has the last non-digit character we clicked.

  if(d == '='){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Answer: ");
    lcd.setCursor(0, 1);
    lcd.print(answer);
    delay(5000);
  } else {
    lcd.clear();
    lcd.print("Please press =");
    return;
  }

  //Check out the other prototype where I added operation precedent and multiple operands.
  
}

