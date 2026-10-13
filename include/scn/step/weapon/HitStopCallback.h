#ifndef SCN_STEP_WEAPON_HITSTOPCALLBACK_H
#define SCN_STEP_WEAPON_HITSTOPCALLBACK_H

#include "scn/step/chara/IHitStopCallback.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

class HitStopCallback : public chara::IHitStopCallback {
public:
    HitStopCallback(Weapon& weapon);
    virtual ~HitStopCallback();
    virtual void onStart();
    virtual void onEnd();

private:
    Weapon& mObj;
};

}
}
}

#endif
