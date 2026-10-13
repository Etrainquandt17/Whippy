#include "hid/DPD.h"

namespace hid {

DPD::DPD()
    : mDist(0.0f)
    , mPos(Vec2())
    , mHori(Vec2()) {}

void DPD::update(f32 dist, const Vec2& pos, const Vec2& hori) {
    mDist = dist;
    mPos = pos;
    mHori = hori;
}

Vec2 DPD::pos() const {
    return mPos;
}

Vec2 DPD::hori() const {
    return mHori;
}

}
