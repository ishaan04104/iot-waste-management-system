# Arduino Servo Motor Control with Sensors

This project controls three servo motors based on inputs from a PIR sensor, an ultrasonic sensor, and a moisture sensor.

## Components and Their Connections

### Servo Motors
- **servo1**: Controls a lid or flap (connected to PWM pin 3).
- **servo2**: Controls a tilter mechanism (connected to PWM pin 4).
- **servo3**: Also part of the tilter mechanism (connected to PWM pin 6).

### PIR Sensor
- **sensorPin**: Pin 5
- Detects motion. If motion is detected, it returns `HIGH`; otherwise, `LOW`.

### Ultrasonic Sensor
- **trigPin**: Pin 9
- **echoPin**: Pin 10
- Measures distance using sound waves.
  - **trigPin**: Triggers the sensor.
  - **echoPin**: Reads the return signal.

### Moisture Sensor
- **moisturePin**: Analog pin A0
- Reads the moisture level of the soil.

## Code Flow

### Setup
- Sets up the pin modes for the ultrasonic sensor and PIR sensor.
- Attaches the servo motors to their respective pins.
- Initializes serial communication for monitoring.

### Loop
1. **Read PIR Sensor**: The state of the PIR sensor is read.
2. **Measure Distance**: The ultrasonic sensor measures the distance to an object.
3. **Check Conditions**:
   - If the distance is less than 30 cm and motion is detected (`state == HIGH`):
     1. The lid (**servo1**) opens by rotating from 45° to 150°.
     2. The moisture level is read from the soil using the moisture sensor.
     3. Based on the moisture level:
        - If the moisture level is greater than 550, the tilter (**servo2** and **servo3**) tilts one way.
        - Otherwise, it tilts the other way.
     4. The lid (**servo1**) closes by rotating back from 150° to 45°.

