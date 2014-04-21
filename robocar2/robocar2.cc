#include <Arduino.h>

// right-side wheels
#define MOTOR_ENA_PIN 4
#define MOTOR_IN1_PIN 5
#define MOTOR_IN2_PIN 6

// left-side wheels
#define MOTOR_ENB_PIN 8
#define MOTOR_IN3_PIN 9
#define MOTOR_IN4_PIN 10

// delay between commands (in ms)
#define COMMAND_DELAY 200

void moveForward() {
    digitalWrite(MOTOR_ENA_PIN, LOW);
    digitalWrite(MOTOR_ENB_PIN, LOW);
    digitalWrite(MOTOR_IN1_PIN, HIGH);
    digitalWrite(MOTOR_IN2_PIN, LOW);
    digitalWrite(MOTOR_IN3_PIN, HIGH);
    digitalWrite(MOTOR_IN4_PIN, LOW);
    digitalWrite(MOTOR_ENA_PIN, HIGH);
    digitalWrite(MOTOR_ENB_PIN, HIGH);
}


void moveBackward() {
    digitalWrite(MOTOR_ENA_PIN, LOW);
    digitalWrite(MOTOR_ENB_PIN, LOW);
    digitalWrite(MOTOR_IN1_PIN, LOW);
    digitalWrite(MOTOR_IN2_PIN, HIGH);
    digitalWrite(MOTOR_IN3_PIN, LOW);
    digitalWrite(MOTOR_IN4_PIN, HIGH);
    digitalWrite(MOTOR_ENA_PIN, HIGH);
    digitalWrite(MOTOR_ENB_PIN, HIGH);
}


void turnRight() {
    digitalWrite(MOTOR_ENA_PIN, LOW);
    digitalWrite(MOTOR_ENB_PIN, LOW);
    digitalWrite(MOTOR_IN1_PIN, LOW);
    digitalWrite(MOTOR_IN2_PIN, LOW);
    digitalWrite(MOTOR_IN3_PIN, HIGH);
    digitalWrite(MOTOR_IN4_PIN, LOW);
    digitalWrite(MOTOR_ENA_PIN, HIGH);
    digitalWrite(MOTOR_ENB_PIN, HIGH);
}


void turnLeft() {
    digitalWrite(MOTOR_ENA_PIN, LOW);
    digitalWrite(MOTOR_ENB_PIN, LOW);
    digitalWrite(MOTOR_IN1_PIN, HIGH);
    digitalWrite(MOTOR_IN2_PIN, LOW);
    digitalWrite(MOTOR_IN3_PIN, LOW);
    digitalWrite(MOTOR_IN4_PIN, LOW);
    digitalWrite(MOTOR_ENA_PIN, HIGH);
    digitalWrite(MOTOR_ENB_PIN, HIGH);
}


void stopMotors() {
    digitalWrite(MOTOR_ENA_PIN, LOW);
    digitalWrite(MOTOR_ENB_PIN, LOW);
    digitalWrite(MOTOR_IN1_PIN, LOW);
    digitalWrite(MOTOR_IN2_PIN, LOW);
    digitalWrite(MOTOR_IN3_PIN, LOW);
    digitalWrite(MOTOR_IN4_PIN, LOW);
}


void setup() {
    Serial.begin(9600);

    // configure motor PINs
    pinMode(MOTOR_ENA_PIN, OUTPUT);
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);
    pinMode(MOTOR_ENB_PIN, OUTPUT);
    pinMode(MOTOR_IN3_PIN, OUTPUT);
    pinMode(MOTOR_IN4_PIN, OUTPUT);
}


void loop() {

#if 0
    byte in = 0;

    while (Serial.available()) {
        // read the incoming byte:
        in = Serial.read();
        // Serial.write(in);
    }

    switch(in) {
    case 'F': // forward
    case 'f': // forward
    case '1': // forward
        moveForward(); break;
    case 'B': // backward
    case 'b': // backward
    case '2': // backward
        moveBackward(); break;
    case 'L': // turn left
    case 'l': // turn left
    case '3': // turn left
        turnLeft(); break;
    case 'R': // turn right
    case 'r': // turn right
    case '4': // turn right
        turnRight(); break;
    default:
        stopMotors();
        Serial.write(in);
    }

    delay(COMMAND_DELAY);
#endif
}


#if 0
#include <Arduino.h>

// PIN mapping
// /usr/share/arduino/hardware/arduino/variants/standard/pins_arduino.h

#define ECHO_PIN 2 //(PD2)
#define TRIG_PIN 3 //(PD2)
#define LED_PIN 13

enum State {
    IDLE = 0,
    STARTED,
    FINISHED
};

struct Sonic {
    long start;
    long end;
    State state;
};

volatile Sonic sonic;

ISR (PCINT0_vect) {
    int level = PIND & _BV(ECHO_PIN);
    long us = micros();

    if (level && sonic.state == IDLE) {
        sonic.start = us;
        sonic.state = STARTED;
    } else if (!level && sonic.state == STARTED) {
        sonic.end = us;
        sonic.state = FINISHED;
    } else {
        // noop
    }
}


void setup() {
    Serial.begin(9600);

    pinMode(LED_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);

    // clear trigger
    digitalWrite(TRIG_PIN, LOW);

    sonic.state = IDLE;

    attachInterrupt(INT0, PCINT0_vect, CHANGE);

    Serial.println("setup done");
}


void loop() {
    // LED ON
    digitalWrite(LED_PIN, HIGH);

    // prepare trigger
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(5);

    // clear state
    sonic.start = sonic.end = 0;
    sonic.state = IDLE;

    // fire trigger
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // wait for data;
    while(sonic.state != FINISHED) {
        delayMicroseconds(1);
    }

    long time = sonic.end-sonic.start;

    Serial.print("got: ");
    Serial.print(time);
    Serial.print("us, ");
    Serial.print(time/58);
    Serial.print("cm");
    Serial.println();

    // LED OFF
    digitalWrite(LED_PIN, LOW);

    delay(1000);
}
#endif
