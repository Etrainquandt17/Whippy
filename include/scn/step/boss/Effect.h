#ifndef SCN_STEP_BOSS_EFFECT_H
#define SCN_STEP_BOSS_EFFECT_H

#include "scn/step/chara/Effect.h"

namespace scn {
namespace step {

namespace chara {
class Effect;
}

namespace boss {

class Boss;

class Effect {
public:
    Effect(Boss& boss);

    chara::Effect& back();
    chara::Effect& super();
    chara::Effect& normal();
    chara::Effect& normalWarp();
    chara::Effect& state();
    chara::Effect& stateWarp();
    chara::Effect& fore();
    chara::Effect& stateBack();
    void onStateChange();
    void onHitStopStart();
    void onHitStopEnd();
    void onObjStopStarted();
    void onObjStopFinished();

private:
    Boss& mBoss;
    chara::Effect mSuper;
    chara::Effect mNormal;
    chara::Effect mNormalWarp;
    chara::Effect mState;
    chara::Effect mStateWarp;
    chara::Effect mStateBack;
    chara::Effect mBack;
    chara::Effect mFore;
};

}}}  // namespace scn::step::boss

#endif
