#ifndef HID_STICK_H
#define HID_STICK_H

namespace hid {

class Stick {
public:
    Stick(int max);
    Stick(const Stick& other);

    void update(int x, int y);

private:
    int mMax;
    int mX;
    int mY;
};

}

#endif
