#ifndef HID_ACCEL_H
#define HID_ACCEL_H

#include "hel/math/Vector3.h"
#include "revolution/mtx.h"

namespace hid {

class Accel {
public:
    Accel();

    void update(const Vec& raw);
    Vec raw() const;
    hel::math::Vector3 rawVector3() const;

private:
    Vec mRaw;
};

}

#endif
