#include <Arduino.h>

#define LED 13

int incomingByte = 0;   // for incoming serial data

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {
    // send data only when you receive data:
    if (Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();

        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        delay(100);
    }
}
