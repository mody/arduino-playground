#include <Arduino.h>
#include <avr/interrupt.h>

/*
 * /usr/share/arduino/hardware/arduino/variants/standard/pins_arduino.h
 * /usr/share/arduino/hardware/arduino/cores/arduino/Arduino.h
 */

#define LED_PIN 13 // PB5 (D 13)

volatile uint8_t* LED_REG;
uint8_t LED_MASK;

int counter = 0;

// disables PWM on:
// Timer2 (PWM 3 and 11)

void setup() {
    Serial.begin(9600);

    pinMode(LED_PIN, OUTPUT);

    LED_REG = portOutputRegister(digitalPinToPort(LED_PIN));
    LED_MASK = digitalPinToBitMask(LED_PIN);

    *LED_REG |= LED_MASK;


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

    *LED_REG &= ~LED_MASK;
}


ISR(TIMER2_COMPA_vect) {

    if(++counter < 50) {
        return;
    }
    counter = 0;

    // every 100ms here

    *LED_REG ^= LED_MASK;
}


void loop() {
}
