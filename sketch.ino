/*
 * sketch.ino
 * Copyright (C) 2016 czesiek <czesiek@hackerspace.pl>
 *
 * Part of przestszept project/art installation.
 * Loosely based on http://playground.arduino.cc/Code/PIRsense
 *
 * Distributed under terms of the MIT license.
 */
/* vim: set ts=8 sts=8 sw=8 noexpandtab : */


// keyboard report buffer used by pszWrite
uint8_t buf[8] = { 0 };

// the time sensor takes to calibrate
int calibrationTime = 60;  // using HC-SR501

int ledPin = 13;

unsigned int sensorCount = 49;
int sensorPins[49] = {2, 3, 4, 5, 6, 7,  // header 1
  8, 9, 10, 11, 12, 13,  // header 2
  14, 15, 16, 17, 18, 19, 20, 21,  // header 3
  22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,  // header 4
  34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};  // header 5
//char sensorCharacters[49] = {'a', 'b', 'c', 'd', 'e', 'f',
//  'g', 'h', 'i', 'j', 'k', 'l',
//  'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
//  'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F',
//  'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W'};
long unsigned int triggerTime[49];

// the amount of milliseconds the sensor has to be low 
// before we assume all motion has stopped
long unsigned int triggerDelay = 9000;


void setup() {
  // set baudrate
  Serial.begin(9600);

  // initialize sensor pins
  // zero out trigger time (none of the sensors has been triggered before)
  for (int i = 0; i < sensorCount; i++) {
    pinMode(sensorPins[i], INPUT);
    triggerTime[i] = 0;
  }

  // initialize LED pin (for calibration blinking)
  pinMode(ledPin, OUTPUT);

  // give sensors some time to calibrate
  for (int i = 0; i < calibrationTime; i++) {
    // Note: this takes ~1s as pszBlink() takes 200ms
    pszBlink();
    pszBlink();
    pszBlink();
    pszBlink();
    pszBlink();
  }
}


void loop() {
  for (int i = 0; i < sensorCount; i++) {
    if(digitalRead(sensorPins[i]) == HIGH && (millis() - triggerTime[i] > triggerDelay)) {
      // save trigger time
      triggerTime[i] = millis();

      pszWrite(i);
    }
  }
}

// ---- Helpers ----

void pszWrite(int sensorIndex) {
  // we use IDs 4-52 from HID Usage Tables, which correspond to:
  // a-z 0-9 RET ESC DEL TAB SPACE - = [ ] \ # ; '
  
  // keypress
  buf[2] = sensorIndex + 4;  // sensorIndex + 4 = HID Usage ID
  Serial.write(buf, 8);

  // release
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);
}

void pszBlink() {
  // Note: sensor calibration in setup() depends on this taking 200ms

  digitalWrite(ledPin, HIGH);  delay(100);
  digitalWrite(ledPin, LOW);   delay(100);
}
