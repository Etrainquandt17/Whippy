#ifndef SCN_STEP_WEAPON_SUPERSTOP_H
#define SCN_STEP_WEAPON_SUPERSTOP_H

#include "scn/step/spstop/IEventReceiver.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

class SuperStop : public spstop::IEventReceiver {
public:
    SuperStop(Weapon& weapon);
    virtual ~SuperStop();
    virtual void onSuperStopStarted(const spstop::Manager& manager);
    virtual void onSuperStopFinished(const spstop::Manager& manager);

    void onObjCollReactHit();

private:
    Weapon& mObj;
    bool mIsBornInStop;
    bool mIsSpecial;
};

}
}
}

#endif
