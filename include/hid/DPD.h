#ifndef HID_DPD_H
#define HID_DPD_H

#include "revolution/mtx.h"
#include "types.h"

namespace hid {

class DPD {
public:
    DPD();

    void update(f32 dist, const Vec2& pos, const Vec2& hori);
    Vec2 pos() const;
    Vec2 hori() const;

private:
    f32 mDist;
    Vec2 mPos;
    Vec2 mHori;
};

}  // namespace hid

#endif
