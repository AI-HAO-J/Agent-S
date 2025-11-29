# Obstacle-Avoiding Rover

A simple Arduino-based obstacle-avoiding rover using an L298N motor driver and HC-SR04 ultrasonic sensor.

## Overview

This project implements a basic autonomous rover that:
- Drives forward continuously
- Detects obstacles using an ultrasonic sensor
- Backs up and turns randomly (left or right) when an obstacle is detected
- Resumes forward motion after avoiding the obstacle

## Hardware Requirements

- **Microcontroller**: Arduino Uno (or compatible board)
- **Motor Driver**: L298N Dual H-Bridge Motor Driver
- **Distance Sensor**: HC-SR04 Ultrasonic Sensor
- **Motors**: 2x DC gear motors (6V-12V)
- **Power**: Battery pack (7.4V-12V for motors)
- **Chassis**: Robot chassis with wheels and caster

## Pin Configuration

| Arduino Pin | Connection | Description |
|-------------|------------|-------------|
| 5 (PWM) | ENA | Left motor speed |
| 8 | IN1 | Left motor direction 1 |
| 9 | IN2 | Left motor direction 2 |
| 6 (PWM) | ENB | Right motor speed |
| 10 | IN3 | Right motor direction 1 |
| 11 | IN4 | Right motor direction 2 |
| 2 | TRIG | Ultrasonic trigger |
| 3 | ECHO | Ultrasonic echo |

See [wiring.txt](wiring.txt) for detailed wiring instructions.

## Parameters

You can adjust these constants in the code:

| Parameter | Default | Description |
|-----------|---------|-------------|
| `FORWARD_SPEED` | 180 | Motor speed when driving forward (0-255) |
| `TURN_SPEED` | 170 | Motor speed when turning (0-255) |
| `OBSTACLE_DISTANCE_CM` | 25 | Distance threshold for obstacle detection (cm) |
| `ULTRASONIC_TIMEOUT_MICROS` | 30000 | Sensor timeout in microseconds (~5m max range) |
| `MICROSECONDS_PER_CM_ROUNDTRIP` | 58 | Calibration constant for distance calculation |

## Usage

1. Wire the components according to [wiring.txt](wiring.txt)
2. Open `obstacle_avoiding_rover.ino` in the Arduino IDE
3. Select your board and port
4. Upload the sketch
5. Power up the motors and place the rover on the ground

## Serial Monitor

Open the Serial Monitor at 9600 baud to view distance readings in real-time.

## Behavior

1. **Normal operation**: Rover drives forward at `FORWARD_SPEED`
2. **Obstacle detected** (distance < `OBSTACLE_DISTANCE_CM`):
   - Stop motors
   - Back up for 400ms
   - Turn randomly left or right for 350ms
   - Resume forward motion
3. **No reading** (sensor timeout): Continue current behavior

## Troubleshooting

- **Motors not spinning**: Check motor power supply and L298N connections
- **Motors spinning wrong direction**: Swap motor wire polarity or adjust IN1-IN4 logic
- **Rover not detecting obstacles**: Verify HC-SR04 wiring, check Serial Monitor for readings
- **Erratic behavior**: Ensure common ground between Arduino and motor power supply

## License

This example is provided as-is for educational purposes.
