#include <Servo.h>

Servo servo1; // Create object for Servo motor 1
Servo servo2; // Create object for Servo motor 2
Servo servo3; // Create object for Servo motor 3

int position = 0; // Variable to store the position
const int trigPin = 9;
const int echoPin = 10;
int sensorPin = 5; // PIR Outpin
const int moisturePin = A0; // Analog pin connected to the sensor
int state = 0; // PIR status
long duration;
int distance;

void setup() {
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(sensorPin, INPUT);
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600); // Starts the serial communication
    servo1.attach(3); // Set PWM pin 3 for Servo motor 1 lid
    servo2.attach(4); // Set PWM pin 4 for Servo motor 2 tilter
    servo3.attach(6); // Set PWM pin 6 for Servo motor 3 tilter
}

void loop() {
    state = digitalRead(sensorPin);
    Serial.print("State: ");
    Serial.print(state);
    Serial.println("");

    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = duration * 0.034 / 2.0;

    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);

    if (distance < 30 && state == HIGH) {
        for (int i = 45; i <= 150; i += 5) {
            servo1.write(i); // Set position of Servo motor 1
            delay(50);
        }
        delay(5000);

        int sensorValue = analogRead(moisturePin);
        Serial.print("Moisture Level: ");
        Serial.print(sensorValue);
        Serial.println();

        servo2.write(90);

        if (sensorValue > 550) {
            for (int i = 90; i >= 45; i -= 5) {
                servo2.write(i);
                servo3.write(i);
                delay(50);
            }
            delay(2000);
            for (int i = 45; i <= 90; i += 5) {
                servo2.write(i);
                servo3.write(i);
                delay(50);
            }
        } else {
            for (int i = 90; i <= 135; i += 5) {
                servo2.write(i);
                servo3.write(i);
                delay(50);
            }
            delay(2000);
            for (int i = 135; i >= 90; i -= 5) {
                servo2.write(i);
                servo3.write(i);
                delay(50);
            }
        }

        for (int i = 150; i >= 45; i -= 5) {
            servo1.write(i); // Set position of Servo motor 1
            delay(50);
        }
    }
}
