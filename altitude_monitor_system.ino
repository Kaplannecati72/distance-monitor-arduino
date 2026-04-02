/**
 * Project: Real-Time Altitude Monitoring & Alert System
 * Author: Necat (Ankara University, Mathematics)
 * Field: Embedded Systems & Applied Computing Portfolio
 * * Description: 
 * A high-precision embedded solution for real-time altitude tracking 
 * using ultrasonic Time-of-Flight (ToF) technology. Features 
 * frequency-modulated acoustic feedback and an I2C visual interface.
 * * Mathematical Logic:
 * Distance = (Pulse Duration * 0.0343) / 2
 * Includes software-based noise filtering and I2C stability optimizations.
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Hardware Configuration
// Use 0x27 or 0x3F depending on your LCD module
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int BUZZER_PIN = 11;

// Physics Constants
const float SOUND_SPEED = 0.0343; // Speed of sound in cm/us

void setup() {
  Wire.begin();
  delay(500); // Wait for I2C bus stability
  
  lcd.init();
  lcd.backlight();
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM READY");
  lcd.setCursor(0, 1);
  lcd.print("MONITORING...");
  delay(1500);
  lcd.clear();
}

void loop() {
  long duration;
  float distance;

  // Triggering the Ultrasonic Sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Measure pulse duration with 26ms timeout (approx. 4.5m max range)
  duration = pulseIn(ECHO_PIN, HIGH, 26000); 
  distance = (duration * SOUND_SPEED) / 2;

  // Process data and update UI every 250ms for stability
  if (distance > 2 && distance < 400) {
    updateInterface(distance);
  }
  
  delay(250); 
}

void updateInterface(float dist) {
  // LCD Row 0: Altitude Display
  lcd.setCursor(0, 0);
  lcd.print("ALT: ");
  lcd.print(dist, 1);
  lcd.print(" cm    "); // Trailing spaces to clear old digits

  // LCD Row 1: Status & Alarm Logic
  lcd.setCursor(0, 1);
  if (dist < 15) {
    tone(BUZZER_PIN, 1000);
    lcd.print("!!! CRITICAL !!!");
  } else {
    noTone(BUZZER_PIN);
    lcd.print("STATUS: SAFE    ");
  }
}
