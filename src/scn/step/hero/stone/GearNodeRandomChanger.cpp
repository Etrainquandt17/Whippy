#include "scn/step/hero/stone/GearNodeRandomChanger.h"
#include "app/Random.h"
#include "hel/common/Array.h"
#include "scn/step/DebugStepSettingProxy.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

GearNodeRandomChanger::GearNodeRandomChanger(Gear& gear)
    : mGear(gear)
    , mSelectedIndex(0)
    , mNum(0)
    , mIsSelected(false) {
}

GearNodeRandomChanger::~GearNodeRandomChanger() {
}

void GearNodeRandomChanger::select(const u32* table, u32 num) {
    if (DebugStepSettingProxy::GetHeroSettingStoneKind() != 0) {
        mSelectedIndex = DebugStepSettingProxy::GetHeroSettingStoneKind() - 1;
        mNum = num;
        mIsSelected = true;
        return;
    }
    hel::common::Array<u32, 16> sums;
    u32 total = 0;
    for (u32 i = 0; i < num; i++) {
        total += table[i];
        sums[i] = total;
    }
    u32 value = app::Random::RandU32(total);
    mIsSelected = false;
    for (u32 i = 0; i < num; i++) {
        if (value < sums[i]) {
            mSelectedIndex = i;
            mNum = num;
            mIsSelected = true;
            return;
        }
    }
}

u32 GearNodeRandomChanger::selectedIndex() const {
    return mSelectedIndex;
}

}
}
}
}
