// Simple obstacle-avoiding rover for Arduino + L298N + HC-SR04
// Motors: two DC motors via L298N (enable pins tied high or PWM on ENA/ENB)
// Ultrasonic: HC-SR04 on TRIG_PIN / ECHO_PIN
// Wiring: see wiring.txt

const int ENA = 5; // PWM for left motor (or motor A)
const int IN1 = 8;
const int IN2 = 9;

const int ENB = 6; // PWM for right motor (or motor B)
const int IN3 = 10;
const int IN4 = 11;

const int TRIG_PIN = 2;
const int ECHO_PIN = 3;

const int FORWARD_SPEED = 180; // 0-255
const int TURN_SPEED = 170;
const unsigned long OBSTACLE_DISTANCE_CM = 25; // threshold

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
  stopMotors();
  delay(200);
}

void loop() {
  long dist = readUltrasonicCm();
  Serial.print("Distance (cm): ");
  Serial.println(dist);

  if (dist > 0 && dist < OBSTACLE_DISTANCE_CM) {
    // Obstacle detected: back up, then turn randomly left or right
    stopMotors();
    delay(50);
    driveBackward(FORWARD_SPEED);
    delay(400);
    stopMotors();
    delay(100);
    if (random(0, 2) == 0) {
      turnLeft(TURN_SPEED);
    } else {
      turnRight(TURN_SPEED);
    }
    delay(350);
    stopMotors();
    delay(100);
  } else {
    // Clear: drive forward
    driveForward(FORWARD_SPEED);
  }
  delay(50);
}

long readUltrasonicCm() {
  // Send trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo pulse
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms => ~5m
  if (duration == 0) return -1; // no reading
  long cm = duration / 29 / 2;
  return cm;
}

void driveForward(int speed) {
  // Left motor forward
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Right motor forward
  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void driveBackward(int speed) {
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft(int speed) {
  // Left motor backward, right motor forward
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight(int speed) {
  // Left motor forward, right motor backward
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
