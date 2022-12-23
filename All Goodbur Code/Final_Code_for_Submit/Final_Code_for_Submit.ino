/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor-servo-motor
*/

#include <Servo.h>

// constants won't change
const int TRIG_PIN  = 6;      // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN  = 7;      // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int SERVO_1 = 9;        // Arduino pin connected to Servo (Eye Motion) Motor's pin
const int SERVO_2 = 2;        // Arduino pin connected to Servo (Hand Trap) Motor's pin
const int SERVO_3 = 4;        // Arduino pin connected to Servo (Mouth Expression Rotation) Motor's pin
const int buttonPin = 11;     // Ardino Pin connected to Button (Hand Trap Relase) 

int leds = 8;                 // Ardino Pin connected to Two LED's (Tear drops)
int ledSmall = 3;             // Ardino Pin connected to single small LED (Tear drop)
int buttonState = 0;          // Variable for reading the pushbutton status

Servo servo1;                 // create servo object to control a servo (Eye Motion)
Servo servo2;                 // create servo object to control a servo (Hand Trap)
Servo servo3;                 // create servo object to control a servo (Mouth Expression Rotation)
int pos = 0;                  // variable to store the servo position
int state = 0; 

// variables will change:
float duration_us;                                   // distance_cm;
int distance_cm = 0.017 * duration_us;               // distance calculation using duration_us (pulse)

int mydistance = 0;                                  // variable to store distance value 

int getDistance() {                                  // proximity sensor set up
  digitalWrite(TRIG_PIN, HIGH);                      // Turn trig pin on
  delayMicroseconds(10);                             // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, LOW);                       // Turn trig pin off

  duration_us = pulseIn(ECHO_PIN, HIGH);             // measure duration of pulse from ECHO pin
  distance_cm = 0.017 * duration_us;                 // calculate the distance
  return (distance_cm);
}
int getCapsense() {                                  // touch capacitor set up
  int cap_reading = analogRead(A0);                  // cap_reading value dirived from reading analog pin A0
  float volt_reading = (5.0 / 1023.0) * cap_reading; // Convert 10-bit ADC value (0 - 1023) to the actual voltage reading (0 - 5V)
  Serial.print(volt_reading);                        // Print Volt reading value to serial monitor
  Serial.println(" Volts");                          // Print 'volts' after reading value on serial monitor.

}

void setup() {
  Serial.begin (9600);          // initialize serial port
  pinMode(TRIG_PIN, OUTPUT);    // set arduino pin to output mode
  pinMode(leds, OUTPUT);        // set arduino pin to output mode
  pinMode(ledSmall, OUTPUT);    // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);     // set arduino pin to input mode
  pinMode(buttonPin, INPUT);    // set arduino pin to input mode

  servo1.attach(SERVO_1);       // attaches servo1 on pin 9 to the servo object
  servo1.write(120);            // Eyes Motion servo rotates to 120 degree start angle
  servo2.attach(SERVO_2);       // attaches servo2 on pin 4 to the servo object
  servo2.write(180);            // Hand Trap servo rotates to 180 degree start angle
  servo3.attach(SERVO_3);       // attaches servo3 on pin 2 to the servo object
  servo3.write(130);            // Mouth Expression Rotation servo rotates to 130 degree start angle
  digitalWrite(leds, LOW);      // Turn LED's off
  digitalWrite(ledSmall, LOW);  // Turn LED off
  
}

void loop() {


  if(digitalRead(buttonPin)== HIGH) {          // If button pin is pressed/High
    Serial.println("button pressed");          // print 'button pressed' to serial monitor
  
  }
    buttonState = digitalRead(buttonPin);      // Button state on/off derived from digital read of button pin
 
    mydistance = getDistance();                // mydistance value derived from getDistance integer
    Serial.print("distance: ");                // print 'distance' to Serial Monitor
    Serial.print(mydistance);                  // print distance value  to Serial Monitor
    Serial.println(" cm");                     // print 'cm' to Serial Monitor
    delay(500);                                // pause for 500ms

    getCapsense();                                        // calling getCapsense integer
    int cap_reading = analogRead(A0);                     // cap_reading value dirived from reading analog pin A0
    float volt_reading = (5.0 / 1023.0) * cap_reading;    // Convert 10-bit ADC value (0 - 1023) to the actual voltage reading (0 - 5V)


/////////// switch case statements begin //////////////////////////   


    switch (state) {
      
// in state 0, blink leds and listen to the distance sensor until it gets to less than 10cm, then switch to state 1.
      case 0: 
        Serial.println("State 0:");                 // print State 0 to serial monitor 
        digitalWrite(leds, HIGH);                   // turn tear leds on
        digitalWrite(ledSmall, HIGH);               // turn small tear led on
        delay (100);                                // pause for 100ms
        digitalWrite(leds, LOW);                    // turn tear leds off
        digitalWrite(ledSmall, LOW);                // turn small tear led off
        delay (100);                                // pause for 100ms

        if (getDistance() < 10) {                   // if proximity sensor distancs reads less than 10cm
          Serial.println("Changing to state 1.");   // print phrase to serial monitor
          state = 1;                                //change to state 1
        }
        break;

        
// in case 1 listen for distance until it's less than 6cm and then move the servo into position 
      case 1: 
        Serial.println("State 1:");                 // print State 1 to serial monitor 
        digitalWrite(leds, HIGH);                   // turn tear leds on
        digitalWrite(ledSmall, LOW);                // turn small tear led off
        servo1.write(80);                           // Rotate Eye Motion servo to 80 degrees so eyes are looking foward
        delay (200);                                // pause for 200ms
        if (getDistance() < 6 ) {                   // if proximity sensor distancs reads less than 6cm
          Serial.println("Changing to state 2.");   // print phrase to serial monitor
          state = 2;                                //change to state 2
        }
        break;


// in case 2 the servo will sweep between 55 and 130 degrees untill the touch capacitor has been touched and then change state
      case 2: 
        Serial.println("State 2:");                 // print State 2 to serial monitor 
        digitalWrite(leds, LOW);                    // turn tear leds on
        if (getDistance() < 6 ) {
          for (pos = 55; pos <= 130; pos += 1) {    // Eye Motion servo rotates from 55to 130 degrees in steps of 1 degree
            servo1.write(pos);                      // tell servo to go to position in variable 'pos'
            delay(60);                              // waits 60 ms for the servo to reach the position
          }

          for (pos = 130; pos >= 55; pos -= 1) {    // Eye Motion rotates from 130 degrees to 55 degrees
            servo1.write(pos);                      // tell servo to go to position in variable 'pos'
            delay(60);                              // waits 60 ms for the servo to reach the position
          }
        }

        if (volt_reading > 1.5 ) {                  // If volt reading on touch capactior is higher than 1.5volts (touched)
          Serial.println("Changing to state 3.");   // print phrase to serial monitor
          state = 3;                                //change to state 3
        }
        break;

        
// in case 3 rotate servos and then switch to state 4
      case 3: 
        Serial.println("State 3:");                 // print State 3 to serial monitor 
        servo2.write(140);                          // Rotate Hand Trap servo to 140 degrees
        delay(2000);                                // pause 2000ms
        servo3.write(0);                            // Rotate Mouth Expression to 0 degrees to smile
        delay(2000);                                // pause 2000ms
        Serial.println("Changing to state 4.");     // print phrase to serial monitor
        state = 4;                                  //change to state 4

        break;


// in case 4 rotate servo and wait for button to be pressed - switching to case 5
      case 4: 
        Serial.println("State 4:");                 // print State 4 to serial monitor 
        servo1.write(110);                          // rotate eye motion servor to 110 degrees 
        delay(2000);                                // pause 2000ms
        if (digitalRead(buttonPin) == HIGH) {       // if button is pressed/high
          Serial.println("Changing to state 5.");   // print phrase to serial monitor
          state = 5;                                //change to state 5
        }

        break;


// in case 5 the Hand trap servo rotates to release the users hand
      case 5:
        Serial.println("State 5:");                 // print State 5 to serial monitor 
        servo2.write(180);                          // Hand Trap servo rotates 180 degrees and releases hand
        delay(2000);                                // pause 2000ms

      default: {
          digitalWrite(leds, LOW);
          digitalWrite(ledSmall, LOW);
        }
        break;

    }
  }
}
