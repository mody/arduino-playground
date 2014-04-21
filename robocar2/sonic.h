#include <Arduino.h>

namespace Mody {

struct Sonic {
    void setup();

    void ping();
    long range();

    bool available() const;
};


}
