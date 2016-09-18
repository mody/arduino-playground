/*
  Example for receiving

  https://github.com/sui77/rc-switch/

  If you want to visualize a telegram copy the raw data and
  paste it into http://test.sui.li/oszi/
*/

#include <Arduino.h>
#include <RCSwitch.h>

static void output(unsigned long decimal, unsigned int length, unsigned int delay,
                   unsigned int* raw, unsigned int protocol);

static const char* bin2tristate(const char* bin);
static char* dec2binWzerofill(unsigned long Dec, unsigned int bitLength);

constexpr int LED      = 13;
constexpr int DATA_PIN = 2;

RCSwitch mySwitch = RCSwitch();

unsigned long time            = 0;
constexpr unsigned long delta = 1000 * 2;

void setup()
{
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
    Serial.begin(9600);
    mySwitch.enableReceive(
        digitalPinToInterrupt(DATA_PIN)); // Receiver on interrupt 0 => that is pin #2
    delay(500);
    Serial.println("Ready");
    digitalWrite(LED, LOW);

    time = millis() + delta;
}

void loop()
{
    if (mySwitch.available()) {
        output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(),
               mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),
               mySwitch.getReceivedProtocol());
        mySwitch.resetAvailable();
    }
}

static void output(unsigned long decimal, unsigned int length, unsigned int delay,
                   unsigned int* raw, unsigned int protocol)
{

    if (decimal == 0) {
        Serial.print("Unknown encoding.");
    } else {
        const char* b = dec2binWzerofill(decimal, length);
        Serial.print("Decimal: ");
        Serial.print(decimal);
        Serial.print(" (");
        Serial.print(length);
        Serial.print("Bit) Binary: ");
        Serial.print(b);
        Serial.print(" Tri-State: ");
        Serial.print(bin2tristate(b));
        Serial.print(" PulseLength: ");
        Serial.print(delay);
        Serial.print(" microseconds");
        Serial.print(" Protocol: ");
        Serial.println(protocol);
    }

    Serial.print("Raw data: ");
    for (unsigned int i = 0; i <= length * 2; i++) {
        Serial.print(raw[i]);
        Serial.print(",");
    }
    Serial.println();
    Serial.println();
}

static const char* bin2tristate(const char* bin)
{
    static char returnValue[50];
    int pos  = 0;
    int pos2 = 0;
    while (bin[pos] != '\0' && bin[pos + 1] != '\0') {
        if (bin[pos] == '0' && bin[pos + 1] == '0') {
            returnValue[pos2] = '0';
        } else if (bin[pos] == '1' && bin[pos + 1] == '1') {
            returnValue[pos2] = '1';
        } else if (bin[pos] == '0' && bin[pos + 1] == '1') {
            returnValue[pos2] = 'F';
        } else {
            return "not applicable";
        }
        pos = pos + 2;
        pos2++;
    }
    returnValue[pos2] = '\0';
    return returnValue;
}

static char* dec2binWzerofill(unsigned long Dec, unsigned int bitLength)
{
    static char bin[64];
    unsigned int i = 0;

    while (Dec > 0) {
        bin[32 + i++] = ((Dec & 1) > 0) ? '1' : '0';
        Dec           = Dec >> 1;
    }

    for (unsigned int j = 0; j < bitLength; j++) {
        if (j >= bitLength - i) {
            bin[j] = bin[31 + i - (j - (bitLength - i))];
        } else {
            bin[j] = '0';
        }
    }
    bin[bitLength] = '\0';

    return bin;
}
