#ifndef SCN_STEP_WEAPON_STATECALLBACK_H
#define SCN_STEP_WEAPON_STATECALLBACK_H

#include "types.h"
#include "util/IStateCallback.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

class StateCallback : public util::IStateCallback {
public:
    StateCallback(Weapon& weapon);

    virtual void onStateChanged(const util::IStateChanger& changer);

private:
    Weapon& mObj;
};

}
}
}

#endif
