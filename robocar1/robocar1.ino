// #include <Arduino.h>
// #include <IRremote.h>

// #define IR_PIN 11

#define MOTOR_ENA_PIN 6
#define MOTOR_IN1_PIN 7
#define MOTOR_IN2_PIN 8

#define MOTOR_ENB_PIN 3
#define MOTOR_IN3_PIN 5
#define MOTOR_IN4_PIN 4

// delay between commands (in ms)
#define COMMAND_DELAY 200

#if 0
// IR READER
IRrecv irrecv(IR_PIN);
decode_results results;


int decode_ir(unsigned long value) {
    static int last_code = '\x0';
    int ret = 0;
    switch(value) {
    case 0xFFFFFFFF:
        ret = last_code; break;
    case 0xFF6897:
        ret = '1'; break;
    case 0xFF9867:
        ret = '2'; break;
    case 0xFFB04F:
        ret = '3'; break;
    case 0xFF30CF:
        ret = '4'; break;
    case 0xFF18E7:
        ret = '5'; break;
    case 0xFF7A85:
        ret = '6'; break;
    case 0xFF10EF:
        ret = '7'; break;
    case 0xFF38C7:
        ret = '8'; break;
    case 0xFF5AA5:
        ret = '9'; break;
    case 0xFF4AB5:
        ret = '0'; break;
    case 0xFF42BD:
        ret = '*'; break;
    case 0xFF52AD:
        ret = '#'; break;
    case 0xFF629D:
        ret = 'w'; break;
    case 0xFFA857:
        ret = 's'; break;
    case 0xFF22DD:
        ret = 'a'; break;
    case 0xFFC23D:
        ret = 'd'; break;
    case 0xFF02FD:
        ret = ' '; break;
    }
    last_code = ret;
    return ret;
}

#endif

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

    // irrecv.enableIRIn(); // Start the IR receiver

    // configure motor PINs
    pinMode(MOTOR_ENA_PIN, OUTPUT);
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);
    pinMode(MOTOR_ENB_PIN, OUTPUT);
    pinMode(MOTOR_IN3_PIN, OUTPUT);
    pinMode(MOTOR_IN4_PIN, OUTPUT);

}


void loop() {
    byte in = 0;

    while (Serial.available()) {
        // read the incoming byte:
        in = Serial.read();
        // Serial.write(in);
    }

    switch(in) {
    case 'F': // forward
    case 'f': // forward
        moveForward(); break;
    case 'B': // backward
    case 'b': // backward
        moveBackward(); break;
    case 'L': // turn left
    case 'l': // turn left
        turnLeft(); break;
    case 'R': // turn right
    case 'r': // turn right
        turnRight(); break;
    default:
        stopMotors();
        Serial.write(in);
    }

    delay(COMMAND_DELAY);
}
