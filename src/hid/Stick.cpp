#include "hid/Stick.h"

namespace hid {

Stick::Stick(int max)
    : mMax(max)
    , mX(0)
    , mY(0) {}

void Stick::update(int x, int y) {
    mX = x;
    mY = y;
}

}
