#include <Arduino.h>
#include <avr/interrupt.h>

/*
 * /usr/share/arduino/hardware/arduino/variants/standard/pins_arduino.h
 * /usr/share/arduino/hardware/arduino/cores/arduino/Arduino.h
 */

#define LED_PIN 13 // PB5 (D 13)

uint16_t LED_PORT;
uint8_t LED_BIT;

// disables PWM on:
// Timer2 (PWM 3 and 11)

void setup() {
    pinMode(LED_PIN, OUTPUT);

    LED_PORT = digitalPinToPort(LED_PIN);
    LED_BIT = digitalPinToBitMask(LED_PIN);

    LED_PORT |= LED_BIT;

    // dissable interrupts
    cli();

    // WGM21 1 : CTC mode
    // COM2Ax 1,2 : Set OC2A on Compare Match
    TCCR2A &= ~(_BV(WGM21) | _BV(WGM20) | _BV(COM2A1) | _BV(COM2A0));
    TCCR2A |= _BV(WGM21) | _BV(COM2A1) | _BV(COM2A0);

    //set prescaller 1/256
    TCCR2B &= ~(_BV(WGM22) | _BV(CS22) | _BV(CS21) | _BV(CS20));
    TCCR2B |= _BV(CS22) | _BV(CS21);

    // 16MHz with 1/256 prescaler = 2ms
    OCR2A = 125;

    // enable interrupt on CTC
    TIMSK2 |= _BV(OCIE2A);

    // enable interrupts
    sei();

    LED_PORT &= ~LED_BIT;
}


ISR(TIMER2_COMPA_vect) {
    static int counter = 0;

    if(++counter < 50) {
        return;
    }
    counter = 0;

    // every 100ms here

    LED_PORT ^= LED_BIT;
}


void loop() {
}
