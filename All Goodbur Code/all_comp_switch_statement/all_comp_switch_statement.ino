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
const int SERVO_2 = 4; // Arduino pin connected to Servo Motor's pin
const int SERVO_3 = 2; // Arduino pin connected to Servo Motor's pin
const int DISTANCE_THRESHOLD = 10; // centimeters
const int DISTANCE_THRESHOLD1 = 5; // centimeters

int led = 8;

Servo servo1; // create servo object to control a servo
Servo servo2; // create servo object to control a servo
Servo servo3; // create servo object to control a servo
int pos = 0;    // variable to store the servo position

int done = 0;

int state = 0;

// variables will change:
float duration_us; //, distance_cm;
int distance_cm = 0.017 * duration_us;

int getDistance ();
int mydistance=0;
int getCapsense();

void setup() {
  Serial.begin (9600);  // initialize serial port
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output mode
  pinMode(led, OUTPUT);
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode

  servo1.attach(SERVO_1);   // attaches the servo on pin 9 to the servo object
  servo1.write(0);          // set servo start angle
  servo2.attach(SERVO_2);   // attaches the servo on pin 4 to the servo object
  servo2.write(0);          // set servo start angle
  servo3.attach(SERVO_3);   // attaches the servo on pin 2 to the servo object
  servo3.write(0);          // set servo start angle
  digitalWrite(led, LOW);

}

void loop() {

  mydistance = getDistance();
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(mydistance);
  Serial.println(" cm");

  getCapsense();



  

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
      servo1.write(45); // moving servo to posotion
      if (getDistance() <6 ) {
        Serial.println("Changing to state 2.");
        state = 2;
      }
      break;

    case 2: // in case 2 the servo will sweep
      Serial.println("State 2:");
      for (pos = 0; pos <= 60; pos += 1) {  // goes from 0 degrees to 180 degrees in steps of 1 degree
        servo1.write(pos);                     // tell servo to go to position in variable 'pos'
        done = 1;
        delay(15);                             // waits 15 ms for the servo to reach the position
      }
      for (pos = 60; pos >= 0; pos -= 1) {     // goes from 180 degrees to 0 degrees
        servo1.write(pos);                     // tell servo to go to position in variable 'pos'
        done = 1;
        delay(15);
      }
      if (getCapsense() >1.5 ) {
        Serial.println("Changing to state 3.");
        state = 3;
      }


      break;

//    case 3: // in case 1 we listen for distance until it's less than 5 and move the servo to position of blah blah blah
//      Serial.println("State 3:");
//      servo3.write(45); // moving servo to posotion
////      if (getDistance() < 6) {
////        Serial.println("Changing to state 4.");
////        state = 4;
//      }
//      break;
//
//    default: {
//        digitalWrite(led, LOW);
//    }
//        break;
    }

int getDistance() ;
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


int getCapsense() ;
  // touch capacitor set up
  int cap_reading = analogRead(A0);
  // Convert 10-bit ADC value (0 - 1023) to the actual voltage reading (0 - 5V)
  float volt_reading = (5.0 / 1023.0) * cap_reading;
  Serial.print(volt_reading);
  Serial.println(" Volts");


}

//  if (distance_cm > DISTANCE_THRESHOLD) { // creature starts off crying (LED Blink)
//   digitalWrite(led, HIGH);
//    delay(1000);                          // wait for a second
//  digitalWrite(led, LOW);                 // turn the LED off by making the voltage LOW
//  delay(1000);                            // wait for a second
//  }
//

//  if (distance_cm < DISTANCE_THRESHOLD) {  // when user takes step forward eyes look straight
//
// servo1.write(45);                         // rotate servo motor to 90 degree/eye position
// digitalWrite(led, HIGH);                  // LED tears stay still
//
//
//}
//  if ((distance_cm < DISTANCE_THRESHOLD1)&&(done==0)&!(volt_reading>1.5)) {  // user takes second step closer
//
//   // eyes scroll to look at hand and back up at user
//     for (pos = 0; pos <= 60; pos += 1) {  // goes from 0 degrees to 180 degrees in steps of 1 degree
//    servo1.write(pos);                     // tell servo to go to position in variable 'pos'
//    done=1;
//    delay(15);                             // waits 15 ms for the servo to reach the position
//  }
//  for (pos = 60; pos >= 0; pos -= 1) {     // goes from 180 degrees to 0 degrees
//    servo1.write(pos);                     // tell servo to go to position in variable 'pos'
//    done=1;
//    delay(15);                             // waits 15 ms for the servo to reach the position
//  }
// }
//if ((volt_reading>1.5)){      // when creature hand's held and touch capacitor triggered:
//
//     servo2.write(90);        // triggered user hand locking mechanism
//     delay(500);
//     digitalWrite(led, LOW);  // creature stops crying
//     delay(500);
//     servo3.write(90);        // servo spins sad expression to happy smile
//     servo1.write (160);      // creature's eyes look up directly at user
//     delay(2000);
//
//  exit(0);   // exit the Arduino Board.
//
//}  }
