#ifndef SCN_STEP_HERO_STONE_GEARNODERANDOMCHANGER_H
#define SCN_STEP_HERO_STONE_GEARNODERANDOMCHANGER_H

#include "hel/common/NonCopyable.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Gear;
namespace stone {

class GearNodeRandomChanger : private hel::common::NonCopyable {
public:
    GearNodeRandomChanger(Gear& gear);
    ~GearNodeRandomChanger();

    void select(const u32* table, u32 num);
    u32 selectedIndex() const;

private:
    Gear& mGear;
    u32 mSelectedIndex;
    u32 mNum;
    bool mIsSelected;
};

}
}
}
}

#endif
