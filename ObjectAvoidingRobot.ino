/**************************************************
Contributors:       Fawaaz Kamali Siddiqui, Parin Patel
---------------------------------------------------
Last Update:        2-August-2023
===================================================
Description:        This robot is controlled through an Arduino
                    Mega. 2 separate motor drivers are used. An
                    ultrasonic sensor is mounted on top of a servo.
                    If an object is detected in close proximity, 
                    the robot will avoid that direction and move away
                    based on the angle the object is detected at.
===================================================
Connections:        First motor driver
                    enA:                 10
                    enB:                 11
                    in1:                 28
                    in2:                 29
                    in3:                 30
                    in4:                 31
                    Second motor driver
                    enA:                 12
                    enB:                 13
                    in1:                 48
                    in2:                 49
                    in3:                 50
                    in4:                 51
                    trig:                4
                    echo:                5
                    servoPin:            24                        
**************************************************/

#include <Servo.h>


// Variable Declarations 
int pos = 0;
int motorSpeed = 140;
int time = 0;
int distance = 0;
int servoRotation = 250;
int minDistance = 45;   // 45 cm

// first motor driver
int enA_1 = 10;
int enB_1 = 11;
int in1_1 = 28;
int in2_1 = 29;
int in3_1 = 30;
int in4_1 = 31;

// second motor driver
int enA_2 = 12;
int enB_2 = 13;
int in1_2 = 48;
int in2_2 = 49;
int in3_2 = 50;
int in4_2 = 51;

int trigPin = 4;
int echoPin = 5;

int servoPin = 24;


// Instantiations - for devices with seperate libraries
Servo servo;



void setup() {

    // Initialize connections
    Serial.begin(9600);

    servo.attach(servoPin); 

    pinMode(enA_1, OUTPUT);
    pinMode(in1_1, OUTPUT);
    pinMode(in2_1, OUTPUT);
    pinMode(enB_1, OUTPUT);
    pinMode(in3_1, OUTPUT);
    pinMode(in4_1, OUTPUT);

    pinMode(enA_2, OUTPUT);
    pinMode(in1_2, OUTPUT);
    pinMode(in2_2, OUTPUT);
    pinMode(enB_2, OUTPUT);
    pinMode(in3_2, OUTPUT);
    pinMode(in4_2, OUTPUT);

    analogWrite(enA_1, motorSpeed);
    analogWrite(enB_1, motorSpeed);

    analogWrite(enA_2, motorSpeed);
    analogWrite(enB_2, motorSpeed);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

}

void loop() {

    // Main program 

    for (pos = 15; pos <= 150; pos += 45) {
        servo.write(pos);
        distance = getDistance();
        delay(servoRotation);   
        if (distance <= minDistance) {
            stop();
            delay(150);
            if (pos <= 60) {
                rotateLeft();
                delay(500);
            } 
            else if (pos >= 150) {
                rotateRight();
                delay(500);
            }   
            else {  // make complete 180 turn
                rotateRight();
                delay(3000);
            }        
        }   
        else { 
            moveForward();
        }     
    }
    for (pos = 150; pos >= 15; pos -= 45) {
        servo.write(pos);
        distance = getDistance();
        delay(servoRotation);
        if (distance <= minDistance) {
            stop();
            delay(150);
            if (pos <= 60) {
                rotateLeft();
                delay(500);
            } 
            else if (pos >= 150) {
                rotateRight();
                delay(500);
            }   
            else {  // make complete 180 turn
                rotateRight();
                delay(3000);
            }        
        }   
        else { 
            moveForward();
        }
    }

}


// Motor methods

void rotateRight() {
    
    digitalWrite(in1_1, HIGH);
    digitalWrite(in2_1, LOW);
    digitalWrite(in3_1, LOW);
    digitalWrite(in4_1, HIGH);

    digitalWrite(in1_2, HIGH);
    digitalWrite(in2_2, LOW);
    digitalWrite(in3_2, LOW);
    digitalWrite(in4_2, HIGH);

}

void moveForward() {

    digitalWrite(in1_1, LOW);
    digitalWrite(in2_1, HIGH);
    digitalWrite(in3_1, LOW);
    digitalWrite(in4_1, HIGH);

    digitalWrite(in1_2, LOW);
    digitalWrite(in2_2, HIGH);
    digitalWrite(in3_2, LOW);
    digitalWrite(in4_2, HIGH);

}

void rotateLeft() {

    digitalWrite(in1_1, LOW);
    digitalWrite(in2_1, HIGH);
    digitalWrite(in3_1, HIGH);
    digitalWrite(in4_1, LOW);   

    digitalWrite(in1_2, LOW);
    digitalWrite(in2_2, HIGH);
    digitalWrite(in3_2, HIGH);
    digitalWrite(in4_2, LOW);  

}

void stop() {
    
    digitalWrite(in1_1, LOW);
    digitalWrite(in2_1, LOW);
    digitalWrite(in3_1, LOW);
    digitalWrite(in4_1, LOW);

    digitalWrite(in1_2, LOW);
    digitalWrite(in2_2, LOW);
    digitalWrite(in3_2, LOW);
    digitalWrite(in4_2, LOW);

}



// Sensor functions
int getDistance() {

    // collect sensor values
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // calculate distance to object
    time = pulseIn(echoPin, HIGH);
    distance = time * (0.034 / 2); // take out time taken for ping to bounce back
    return distance;    // returns distance in cm   

}


