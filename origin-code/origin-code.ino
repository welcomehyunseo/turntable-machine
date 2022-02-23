// the following variables are unsigned longs because the time, measured in

// milliseconds, will quickly become a bigger number than can be stored in an int.

unsigned long lastDebounceTime = 0;
// the last time the output pin was toggled

unsigned long debounceDelay = 50;
// the debounce time; increase if the output flickers

int buttonState;
// the current reading from the input pin

int lastButtonState = LOW;
// the previous reading from the input pin

const int MOTOR1 = 22;

const int MOTOR2 = 23;

const int MOTOR3_DISK = 24;

const int MOTOR4_CUT = 25

const int LAMP_GREEN = 26;

const int LAMP_RED = 27;

const int PUSH_BUTTON = 30;

const int SENSOR1 = 40;
// Rotate once MOTOR1

const int SENSOR2 = 41;
// Rotate once MOTOR2

const int SENSOR3_1 = 42;
// TurnMOTOR3_DISK then MOTOR1

const int SENSOR3_2 = 43;
// MOTOR3_DISK then MOTOR2

const int SENSOR4 = 44;
// MOTOR4_CUT

const int SENSOR5 = 45;
// Pilot RED LED

int positionOfDisk;
// 1일때 SENSOR3-1, 2일때 SENSOR3-2

int pause = LOW;
// 일시정지. 동작상태가 HIGH 인 경우에

int runState = LOW;
// 동작 상태

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  pinMode(MOTOR3_DISK, OUTPUT);
  pinMode(MOTOR4_CUT, OUTPUT);
  pinMode(LAMP_GREEN, OUTPUT);
  pinMode(LAMP_RED, OUTPUT);
  pinMode(PUSH_BUTTON, INPUT);
  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
  pinMode(SENSOR3_1, INPUT);
  pinMode(SENSOR3_2, INPUT);
  pinMode(SENSOR4, INPUT);
  pinMode(SENSOR5, INPUT);
}

void buttonCheck() {
}

void turnMotor(int motor) {
  if (motor == MOTOR1) {

    digitalWrite(MOTOR1, HIGH);
    delay(200);
    while (digitalRead(SENSOR1) == LOW) {
      // Serial.println("MOTOR2 is running");
      if (digitalRead(SENSOR1) == HIGH) {
        digitalWrite(MOTOR1, LOW);
        break;
      }
    }

    digitalWrite(MOTOR1, LOW);

    if (motor == MOTOR2) {

      digitalWrite(MOTOR2, HIGH);
      delay(500);
      while (digitalRead(SENSOR2) == LOW) {
        Serial.println("MOTOR2 is running");
        if (digitalRead(SENSOR2) == HIGH) {
          digitalWrite(MOTOR2, LOW);
          break;
        }
      }

      digitalWrite(MOTOR2, LOW);
    }

    if (motor == MOTOR3_DISK) {

      digitalWrite(MOTOR3_DISK, HIGH);

      delay(500);
      //센서값이 low가 될때를 기다림.

      Serial.println("MOTOR3_DISK DISK ON MOTOR3_DISK ON ");

      // delay(1000);

      while (!(digitalRead(SENSOR3_1)) && (!digitalRead(SENSOR3_2))) {
        //센서 3-1 과 3-2 가 모두 low 인동안 모터3번을 돌림
        // Serial.println("Motor3 Main is running");
        if (digitalRead(PUSH_BUTTON)) {
          digitalWrite(MOTOR3_DISK, LOW);
          while (digitalRead(PUSH_BUTTON))
            ;
          // 버튼 누르면 일시 정지
          // delay(500);
          Serial.println("모터3 일시정지");
          while (!digitalRead(PUSH_BUTTON)) {
          }
          while (digitalRead(PUSH_BUTTON))
            ;
          //다시 버튼 누면 재개됨
          // delay(500);
          digitalWrite(MOTOR3_DISK, HIGH);
        }

        if ((digitalRead(SENSOR3_1)) || (digitalRead(SENSOR3_2))) {
          //센서 3-1 과 3-2 중 어느 한개가 HIGH 이면 모터3번 정지
          // Serial.println(sensor);
          digitalWrite(MOTOR3_DISK, LOW);
          // Serial.println("MOTOR3_DISK, LOW");
          // delay(1000);
          break;
        }
      }
    }

    if (motor == MOTOR4_CUT) {

      digitalWrite(MOTOR4_CUT, HIGH);

      delay(500);

      while (digitalRead(SENSOR4) == LOW) {

        Serial.println("motor4 cut is running");

        if (digitalRead(SENSOR4) == HIGH) {

          digitalWrite(MOTOR4_CUT, LOW);

          break;
        }
      }

      digitalWrite(MOTOR4_CUT, LOW);
    }
  }
}
void windTape() {
  if (checkPosition() == 1) {
    // 모터1번이 와인딩 위치에 있을 경우
    turnMotor(MOTOR1);
  }
  if (checkPosition() == 2) {
    // 모터2번이 와인딩 위치에 있을 경우
    turnMotor(MOTOR2);
  } else {
    Serial.println("motor is out of posotion");
    delay(3000);
  }
}

void cutTape() {
  Serial.println("turn MOTOR4 CUT");
  delay(2000);
  turnMotor(MOTOR4_CUT);
}

void resetPosition() {
  turnMotor(MOTOR1);
  turnMotor(MOTOR2);
  turnMotor(MOTOR3_DISK);
  turnMotor(MOTOR4_CUT);
}

// 테이핑 위치에 있는 모터를 채크한다. SENSOR3_1 => MOTOR1, SENSOR3_2 => MOTOR2
int checkPosition() {
  if (digitalRead(SENSOR3_1) == HIGH) {
    return 1;
  }

  if (digitalRead(SENSOR3_2) == HIGH) {
    return 2;
  } else {
    turnMotor(MOTOR3_DISK);
    // 디스크의 정위치를 위치를 찾아 돌린다.
  }
}

void debounce() {

  int reading = digitalRead(PUSH_BUTTON);
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      if (digitalRead(SENSOR5) == HIGH) {
        // only toggle the LED if the new button state is HIGH
        if (buttonState == HIGH) {
          // Serial.println("turn on MOTOR3 DISK");
          // delay(1000);
          turnMotor(MOTOR3_DISK);
          // cutTape();
          // delay(1000);
          // windTape();
        }
        // End of if(buttonState == HIGH)
      } else {
        digitalWrite(LAMP_RED, HIGH);
      }
    }
  }

  // digitalWrite(MOTOR3_DISK, ledState);

  lastButtonState = reading;

  // Serial.println(lastButtonState);
}

void loop() {
  if (digitalRead(SENSOR5) == LOW) {
    digitalWrite(LAMP_GREEN, LOW);
    digitalWrite(LAMP_RED, HIGH);
  } else {
    digitalWrite(LAMP_GREEN, HIGH);
    digitalWrite(LAMP_RED, LOW);
    debounce();
    Serial.println("debounce");
  }
}