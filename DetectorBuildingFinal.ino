#include <LiquidCrystal.h>

// LCD Initialization
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Variable Instantiation:
const int blueLED = 8; // Output Pin for Blue LED
const int greenLED = 9; // Output Pin for Green LED
const int redLED = 10; // Output Pin for Red LED
const int tarePin = 6; // Input Pin for Tare Button
const double fsrPin = 0; // Input Pin for Force Sensitive Resistor
float fsrInput; // Number Input from Force Sensitive Resistor (From 0 - 1000)
float fsrVoltage; // Voltage Reading for Force Sensitive Resistor
int tareState = 0; // State of Tare Button
double mass = 0.00; // Mass Reading
double tare = 0.00; // Tare Value
const float a = 2140.072; // Variable for Exponential Equation (y = a * b^x )
const float b = .3018; // Variable for Exponential Equation (y = a * b^x)

// Setup
void setup() {

  lcd.begin(16, 2); // Sets and begins LCD screen with 16 columns and 2 rows
  // Setting Pin Mode for Pins:
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(tarePin, INPUT);
  pinMode(fsrPin, INPUT);

}

void loop() {

  fsrInput = analogRead(fsrPin); // Reads the input from the FSR
  tareState = digitalRead(tarePin); // Reads the input from the Tare Button

// Voltage Calculation
  fsrVoltage = fsrInput/200.00;
  fsrVoltage = 5 - fsrVoltage;

// Mass Calculation
  mass = a * pow(b, fsrVoltage); // Utilizes Exponential Equation

// Tare Function
  if (tareState == HIGH) {
    tare = (mass);
  }
  mass = mass - tare;

// Displays Mass and Voltage
  lcd.print("Mass: ");
  if (fsrVoltage >= 3.96) {
    lcd.setCursor(6, 0);
    lcd.print("           ");        
    lcd.setCursor(6, 0);
    lcd.print("0.00");
    lcd.print("g");
  }
  else {
    lcd.setCursor(6, 0);
    lcd.print(mass);
    lcd.print("g");
  }
  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.print(fsrVoltage);
  lcd.print("V");
  lcd.setCursor(0, 0);
  
// LED Functionality
  // Blue LED
  if ((25 <= mass) && (mass <= 260)) {
    digitalWrite(blueLED, HIGH);
  }
  else {
    digitalWrite(blueLED, LOW);
  }
  
  // Green LED
  if ((261 < mass) && (mass <= 500)) {
    digitalWrite(greenLED, HIGH);
  }
  else {
    digitalWrite(greenLED, LOW);
  }

  // Red LED
  if ((500 < mass) && (mass <= 999)) {
    digitalWrite(redLED, HIGH);
  }
  else {
    digitalWrite(redLED, LOW);
  }

}