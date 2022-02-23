#define MOTOR1 22
#define MOTOR2 23
#define MOTOR3_DISK 24
#define MOTOR4_CUT 25

#define LAMP_GREEN 26
#define LAMP_RED 27

#define PUSH_BUTTON 30

#define SENSOR1 40
#define SENSOR2 41
#define SENSOR3_1 42
#define SENSOR3_2 43
#define SENSOR4 44

#define RUNNING_BUTTON 2

void setup() {
  Serial.begin(9600);
  pinMode(RUNNING_BUTTON, INPUT_PULLUP);
  Serial.println("setup");
  attachInterrupt(digitalPinToInterrupt(RUNNING_BUTTON), myISR, LOW); // trigger when button pressed, but not when released.
}

void myISR() {
  Serial.println("FALLING!");
}

void loop() {

}