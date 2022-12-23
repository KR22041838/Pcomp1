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

int led=8;

Servo servo1; // create servo object to control a servo
Servo servo2; // create servo object to control a servo
Servo servo3; // create servo object to control a servo

// variables will change:
float duration_us, distance_cm;

void setup() {
  Serial.begin (9600);  // initialize serial port
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output mode
   pinMode(led,OUTPUT);
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode
  
  servo1.attach(SERVO_1);   // attaches the servo on pin 9 to the servo object
  servo1.write(0);
  servo2.attach(SERVO_2);   // attaches the servo on pin 4 to the servo object
  servo2.write(0);
  servo3.attach(SERVO_3);   // attaches the servo on pin 2 to the servo object
  servo3.write(0);
  
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

  int cap_reading = analogRead(A0);  
  // Convert 10-bit ADC value (0 - 1023) to the actual voltage reading (0 - 5V)
  float volt_reading = (5.0 / 1023.0)*cap_reading;
  Serial.print(volt_reading);
  Serial.println(" Volts");
  // set the value where the LED turns on

  if (distance_cm < DISTANCE_THRESHOLD) {
    servo1.write(90); // rotate servo motor to 90 degree
    
  }
  if (distance_cm < DISTANCE_THRESHOLD1) {
    servo2.write(45); // rotate servo motor to 90 degree
    
  }

  if (distance_cm > DISTANCE_THRESHOLD) {
   digitalWrite(led, HIGH); 
    delay(1000);                       // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  }

   if (volt_reading>1.5){
    // turn LED on
    digitalWrite(led,HIGH);
    
  } else{
    // otherwise, turn LED off
    digitalWrite(led,LOW);
  }
  delay(20);
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}
