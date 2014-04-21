#include <Arduino.h>

namespace Mody {

struct Motor {
    void setup();
    void forward();
    void backward();
    void left();
    void right();
};

}
