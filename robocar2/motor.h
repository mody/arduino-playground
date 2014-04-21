#include <Arduino.h>

namespace Mody {

struct Motor {
    void setup();

    void forward() const;
    void backward() const;
    void left() const;
    void right() const;
    void stop() const;
};

}
