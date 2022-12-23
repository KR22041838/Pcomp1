/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor-servo-motor
*/

#include <Servo.h>

// constants won't change
const int TRIG_PIN  = 6;  // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN  = 7;  // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int SERVO_1 = 9; // Arduino pin connected to Servo Motor's pin
const int SERVO_2 = 2; // Arduino pin connected to Servo Motor's pin
const int SERVO_3 = 4; // Arduino pin connected to Servo Motor's pin
const int DISTANCE_THRESHOLD = 10; // centimeters
const int DISTANCE_THRESHOLD1 = 5; // centimeters
const int buttonPin = 11;

int leds = 8;
int ledSmall = 3;
int buttonState = 0;

Servo servo1; // create servo object to control a servo
Servo servo2; // create servo object to control a servo
Servo servo3; // create servo object to control a servo
int pos = 0;    // variable to store the servo position

int done = 0;

int state = 0;

// variables will change:
float duration_us; //, distance_cm;
int distance_cm = 0.017 * duration_us;


int mydistance = 0;

int getDistance() {
  // proximity sensor set up
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;
  return (distance_cm);
}
int getCapsense() {
  // touch capacitor set up
  int cap_reading = analogRead(A0);
  // Convert 10-bit ADC value (0 - 1023) to the actual voltage reading (0 - 5V)
  float volt_reading = (5.0 / 1023.0) * cap_reading;
  Serial.print(volt_reading);
  Serial.println(" Volts");

}


// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)


void setup() {
  Serial.begin (9600);  // initialize serial port
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output mode
  pinMode(leds, OUTPUT);
  pinMode(ledSmall, OUTPUT);
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode

  servo1.attach(SERVO_1);   // attaches the servo on pin 9 to the servo object
  servo1.write(100);          // Eyes ---- servo start angle
  servo2.attach(SERVO_2);   // attaches the servo on pin 4 to the servo object
  servo2.write(160);          // Lock ---- servo start angle
  servo3.attach(SERVO_3);   // attaches the servo on pin 2 to the servo object
  servo3.write(0);          // Smile ---- servo start angle
  digitalWrite(leds, LOW);
  digitalWrite(ledSmall, LOW);
  pinMode(buttonPin, INPUT);
}

void loop() {

  unsigned long currentMillis = millis();

  if(digitalRead(buttonPin)== HIGH) {
    Serial.println("button pressed");
  
  }
  

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;


    mydistance = getDistance();
    // print the value to Serial Monitor
    Serial.print("distance: ");
    Serial.print(mydistance);
    Serial.println(" cm");
    delay(500); //

    getCapsense();
    int cap_reading = analogRead(A0);
    // Convert 10-bit ADC value (0 - 1023) to the actual voltage reading (0 - 5V)
    float volt_reading = (5.0 / 1023.0) * cap_reading;

    buttonState = digitalRead(buttonPin);

    switch (state) {
      case 0: // in state 0 we listen to the distance sensor until it gets to less than 10cm, then we switch to state 1.
        Serial.println("State 0:");
        digitalWrite(leds, HIGH);
        digitalWrite(ledSmall, HIGH);
        delay (100);
        digitalWrite(leds, LOW);
        digitalWrite(ledSmall, LOW);
        delay (100);

        if (getDistance() < 10) {
          Serial.println("Changing to state 1.");
          state = 1;
        }
        break;

      case 1: // in case 1 we listen for distance until it's less than 5 and move the servo to position of blah blah blah
        Serial.println("State 1:");
        digitalWrite(leds, HIGH);
        digitalWrite(ledSmall, LOW);
        servo1.write(80); // eyes looking foward
        delay (200);
        if (getDistance() < 6 ) {
          Serial.println("Changing to state 2.");
          state = 2;
        }
        break;


      case 2: // in case 2 the servo will sweep
        Serial.println("State 2:");
        digitalWrite(leds, LOW);
        //if (getCapsense() < 1.5 ){
        if (getDistance() < 6 ) {
          for (pos = 50; pos <= 100; pos += 1) {  // goes from 0 degrees to 180 degrees in steps of 1 degree
            servo1.write(pos);                     // tell servo to go to position in variable 'pos'
            delay(70);                             // waits 15 ms for the servo to reach the position
          }

          for (pos = 100; pos >= 50; pos -= 1) {     // goes from 180 degrees to 0 degrees
            servo1.write(pos);                     // tell servo to go to position in variable 'pos'
            delay(70);
          }
        }

        if (volt_reading > 1.5 ) {
          Serial.println("Changing to state 3.");
          state = 3;
        }
        break;

      case 3: // in case 1 we listen for distance until it's less than 5 and move the servo to position of blah blah blah
        Serial.println("State 3:");
        servo2.write(140); // trap
        delay(2000);
        servo3.write(180); // smile
        delay(2000);
        Serial.println("Changing to state 4.");
        state = 4;

        break;



      case 4: // in case 1 we listen for distance until it's less than 5 and move the servo to position of blah blah blah
        Serial.println("State 4:"); // look at uawe
        servo1.write(30);
        delay(2000);
        if (digitalRead(buttonPin) == HIGH) {
          Serial.println("Changing to state 5.");
          state = 5;
        }

        break;

      case 5:
        Serial.println("State 5:");
        servo2.write(160); // release trap
        delay(2000);

      default: {
          digitalWrite(leds, LOW);
          digitalWrite(ledSmall, LOW);
        }
        break;

    }
  }
}
