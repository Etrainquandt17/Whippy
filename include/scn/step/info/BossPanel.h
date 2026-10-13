#ifndef SCN_STEP_INFO_BOSSPANEL_H
#define SCN_STEP_INFO_BOSSPANEL_H

#include "lyt/Layout.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace step {
namespace info {

class BossPanel {
public:
    void set(f32 rate);
    void damage(f32 rate);
    void heal(f32 rate);
    void setLifeBarRate(f32 rate);
    void transformStart();
    void transformEnd();

private:
    u32 _0;
    lyt::Layout mLayout;
    u8 _194[0xB0C - 0x194];
    f32 _B0C;
    f32 _B10;
    f32 _B14;
    bool _B18;
    bool _B19;
    u8 _B1C[0xB90 - 0xB1C];
    u32 _B90;
    util::FrameCounter _B94;
};

}
}
}

#endif
