#include <Arduino.h>

// PIN mapping
// /usr/share/arduino/hardware/arduino/variants/standard/pins_arduino.h

#define IR_PIN 2 //(PD2)

volatile bool level = false;
volatile int counter = 0;

ISR (ir_isr) {
    level = PIND & _BV(IR_PIN);
    ++counter;
}

void setup() {
    Serial.begin(9600);
    pinMode(IR_PIN, INPUT);
    attachInterrupt(INT0, ir_isr, CHANGE);
}

void loop() {
    static int _counter = 0;
    static bool _level = false;

    if (_level != level || _counter != counter) {
        _level = level;
        _counter = counter;

        Serial.print("cntr: ");
        Serial.print(counter);
        Serial.print("; lvl: ");
        Serial.println(level);
    }
}
