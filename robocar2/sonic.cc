#include "sonic.h"

namespace Mody {

enum {
    ECHO_PIN = 2,
    TRIG_PIN = 12,
};

enum Status {
    IDLE = 0,
    WORKING,
    DONE
};

struct State {
    State() : start(0L), end(0L), status(IDLE)
    { }

    long start;
    long end;
    Status status;
};


volatile static State state;

ISR (PCINT0_vect) {
    int level = PIND & _BV(ECHO_PIN);
    long us = micros();

    if (level && state.status == IDLE) {
        state.start = us;
        state.status = WORKING;
    } else if (!level && state.status == WORKING) {
        state.end = us;
        state.status = DONE;
    } else {
        // noop
    }
}


void Sonic::setup() {
    // setup sonic
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);

    // clear trigger
    digitalWrite(TRIG_PIN, LOW);

    state.status = IDLE;

    attachInterrupt(INT0, PCINT0_vect, CHANGE);
}


void Sonic::ping() {
    if (state.status != IDLE) {
        // USER ERROR!
        return;
    }
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
}

long Sonic::range() {
    long range = 0;
    if (state.status == DONE) {
        //TODO: compite distance
    }
    return range;
}

bool Sonic::available() const {
    return state.status == DONE;
}


}
