/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor-servo-motor
*/

#include <Servo.h>


#include "RunningAverage.h"
RunningAverage myRA(10);
int samples = 0;



// constants won't change
const int TRIG_PIN  = 6;  // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN  = 7;  // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int SERVO_1 = 9; // Arduino pin connected to Servo Motor's pin
const int SERVO_2 = 4; // Arduino pin connected to Servo Motor's pin
const int SERVO_3 = 2; // Arduino pin connected to Servo Motor's pin
const int DISTANCE_THRESHOLD = 10; // centimeters
const int DISTANCE_THRESHOLD1 = 5; // centimeters

int led = 8; //first two tears
//int led = 12; // third tear

float myAverage = 0.0;
int samples = 0;

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
  pinMode(led, OUTPUT);
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode

  servo1.attach(SERVO_1);   // attaches the servo on pin 9 to the servo object
  servo1.write(20);          // Eyes ---- servo start angle
  servo2.attach(SERVO_2);   // attaches the servo on pin 4 to the servo object
  servo2.write(0);          // Lock ---- servo start angle
  servo3.attach(SERVO_3);   // attaches the servo on pin 2 to the servo object
  servo3.write(0);          // Smile ---- servo start angle
  digitalWrite(led, LOW);

}
Serial.begin(115200);
Serial.println("Demo RunningAverage lib");
Serial.print("Version: ");
Serial.println(RUNNINGAVERAGE_LIB_VERSION);
myRA.clear(); // explicitly start clean

void loop() {

  long rn = mydistance(0, 900);
  myRA.addValue(rn * 0.1);
  samples++;
  Serial.print("Running Average: ");
  Serial.println(myRA.getAverage(), 3);

if (samples == 300)
  {
    samples = 0;
    myRA.clear();
  }
  delay(100);
}

 
  //unsigned long currentMillis = millis();

  //if (currentMillis - previousMillis >= interval) {
  // save the last time you blinked the LED
  //previousMillis = currentMillis;
  //Serial.print(previousMillis);
  //Serial.println(" previous time");



  mydistance = getDistance():


                 // print the value to Serial Monitor
                 Serial.print("distance: ");
    Serial.print(mydistance);
    Serial.println(" cm");
    delay(500); //

    getCapsense();
    int cap_reading = analogRead(A0);
    // Convert 10-bit ADC value (0 - 1023) to the actual voltage reading (0 - 5V)
    float volt_reading = (5.0 / 1023.0) * cap_reading;

    switch (state) {
    case 0: // in state 0 we listen to the distance sensor until it gets to less than 10cm, then we switch to state 1.
      digitalWrite(led, HIGH);
      Serial.println("State 0:");
      if (getDistance() < 10) {
        Serial.println("Changing to state 1.");
        state = 1;
      }
      break;

    case 1: // in case 1 we listen for distance until it's less than 5 and move the servo to position of blah blah blah
      Serial.println("State 1:");
      digitalWrite(led, LOW);
      servo1.write(90); // eyes looking foward
      delay (200);
      if (getDistance() < 6 ) {
        Serial.println("Changing to state 2.");
        state = 2;
      }
      break;


    case 2: // in case 2 the servo will sweep
      Serial.println("State 2:");


      //if (getCapsense() < 1.5 ){
      if (getDistance() < 6 ) {
        for (pos = 45; pos <= 90; pos += 1) {  // goes from 0 degrees to 180 degrees in steps of 1 degree
          servo1.write(pos);                     // tell servo to go to position in variable 'pos'
          delay(70);                             // waits 15 ms for the servo to reach the position
        }
        for (pos = 90; pos >= 45; pos -= 1) {     // goes from 180 degrees to 0 degrees
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
      servo2.write(70); // moving servo to posotion
      delay(2000);
      servo3.write(180);
      delay(2000);
      Serial.println("Changing to state 4.");
      state = 4;

      break;



    case 4: // in case 1 we listen for distance until it's less than 5 and move the servo to position of blah blah blah
      Serial.println("State 4:");
      servo1.write(70);
      delay(2000);
      break;

    default: {
        digitalWrite(led, LOW);
      }
      break;

      // }
  }
}
