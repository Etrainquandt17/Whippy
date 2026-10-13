#ifndef SCN_STEP_WEAPON_EFFECT_H
#define SCN_STEP_WEAPON_EFFECT_H

#include "scn/step/chara/Effect.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

class Effect {
public:
    Effect(Weapon& weapon);

    chara::Effect& normal();
    chara::Effect& warp();
    void onHitStopStart();
    void onHitStopEnd();
    void onObjStopStarted();
    void onObjStopFinished();

private:
    Weapon& mObj;
    chara::Effect mNormal;
    chara::Effect mWarp;
};

}}}  // namespace scn::step::weapon

#endif
