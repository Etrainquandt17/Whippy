#include "hid/Accel.h"

namespace hid {

Accel::Accel()
    : mRaw(Vec()) {}

void Accel::update(const Vec& raw) {
    mRaw.x = raw.x;
    mRaw.y = raw.y;
    mRaw.z = raw.z;
}

Vec Accel::raw() const {
    return mRaw;
}

hel::math::Vector3 Accel::rawVector3() const {
    return hel::math::Vector3(mRaw.x, mRaw.y, mRaw.z);
}

}  // namespace hid
