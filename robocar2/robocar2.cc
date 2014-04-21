#include <Arduino.h>

#include "motor.h"
#include "sonic.h"

// PIN mapping
// /usr/share/arduino/hardware/arduino/variants/standard/pins_arduino.h

// delay between commands (in ms)
enum { COMMAND_DELAY = 200 };

Mody::Motor motor;
Mody::Sonic sonic;

void setup() {
    Serial.begin(9600);

    motor.setup();
    sonic.setup();
}


void loop() {
    static long range = 0;
    if (sonic.range(&range)) {
        range /= 58; // convert to cm
    }

    if (range < 30) {
        // TODO : all stop!
    }

    // handle communication

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

