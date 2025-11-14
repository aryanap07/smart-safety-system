#include <LiquidCrystal.h>   // include LCD library

// initialize LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float temp;
float v_out;
float v_out1;
int LED = 13;
int gas_sensor;
int piezo = 7;

void setup() {
  pinMode(A0, INPUT);   // Gas sensor
  pinMode(A1, INPUT);   // LM35
  pinMode(LED, OUTPUT);
  pinMode(piezo, OUTPUT);
  Serial.begin(9600);
  
  lcd.begin(16, 2);    // initialize 16x2 LCD
  lcd.print("System Initializing");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read LM35 sensor
  v_out = analogRead(A1);
  v_out1 = (v_out / 1023.0) * 5000.0;   // convert ADC to mV
  temp = (v_out1 - 500.0) / 10.0;       // convert mV to °C
  
  // Read gas sensor
  gas_sensor = analogRead(A0);
  
  // Display sensor readings
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temp);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("Gas:");
  lcd.print(gas_sensor);
  
  // Conditions
  bool tempHigh = temp >= 75.0;
  bool gasHigh = gas_sensor >= 100;

  // If either temp OR gas exceeds threshold — both LED and buzzer ON
  if (tempHigh && gasHigh) {
    digitalWrite(LED, HIGH);
    digitalWrite(piezo, HIGH);
    lcd.clear();
    lcd.print("ALERT: TEMP+GAS!");
  } 
  else if (tempHigh) {
    digitalWrite(LED, HIGH);
    digitalWrite(piezo, HIGH); // piezo ON together
    lcd.clear();
    lcd.print("HIGH TEMP ALERT!");
  } 
  else if (gasHigh) {
    digitalWrite(LED, HIGH);
    digitalWrite(piezo, HIGH); // piezo ON together
    lcd.clear();
    lcd.print("GAS ALERT!");
  } 
  else {
    digitalWrite(LED, LOW);
    digitalWrite(piezo, LOW);
  }

  // Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C\tGas: ");
  Serial.println(gas_sensor);
  
  delay(1000);
}
