#ifndef SCN_STEP_GIMMICK_POPFLOWER_VACUUMRECEIVER_H
#define SCN_STEP_GIMMICK_POPFLOWER_VACUUMRECEIVER_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {

class Component;

namespace gimmick {
namespace popflower {

// TODO: derives from the vacuum receiver interface (its vtable has 18 entries); only what
// scn/step/gimmick/popflower/PopFlower.cpp calls is declared.
class VacuumReceiver {
public:
    VacuumReceiver(Component& component, const hel::math::Vector2& pos);
    virtual ~VacuumReceiver();

    bool isVacuumed() const;
    void clearVacuumedFlag();

private:
    u32 _4[(0x28 - 0x4) / 4];
};

}
}
}
}

#endif
