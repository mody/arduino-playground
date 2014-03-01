#include <Arduino.h>
#include <avr/interrupt.h>

#define PIN_LED 13

void setup() {
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH);

    // clear WGM2x
    TCCR2A &= ~(_BV(WGM22) | _BV(WGM21) | _BV(WGM20));
    // set WGM21 only = CTC mode
    TCCR2A |= _BV(WGM21);

    OCR2A = 6250; // 100ms with 1/256 prescaler

    digitalWrite(PIN_LED, LOW);
}

void loop() {
}
