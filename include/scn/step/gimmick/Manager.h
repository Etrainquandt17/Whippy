#ifndef SCN_STEP_GIMMICK_MANAGER_H
#define SCN_STEP_GIMMICK_MANAGER_H

#include "hel/math/Vector3.h"
#include "mem/ExplicitScopedPtr.h"
#include "types.h"

namespace scn {
namespace step {
namespace gimmick {

namespace warpstar {
class Manager;
}

namespace shipevent {
class Manager;
}

class SwitchReceiverManager;

class Manager {
public:
    void onEat(const hel::math::Vector3& pos);
    warpstar::Manager& warpStarManager();
    SwitchReceiverManager& switchReceiverManager();
    void onVomit(const hel::math::Vector3& pos);
    void onThroughLand(const hel::math::Vector3& pos);
    void onRun(const hel::math::Vector3& pos);
    void onDrink(const hel::math::Vector3& pos);

    // A unit that uses this defines MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE ahead of its includes.
    shipevent::Manager& shipeventManager() { return mShipeventManager.ref(); }

private:
    // TODO: the members ahead of this one.
    u8 _0[0x1B4];
    mem::ExplicitScopedPtr<shipevent::Manager> mShipeventManager;
};

}
}
}

#endif
