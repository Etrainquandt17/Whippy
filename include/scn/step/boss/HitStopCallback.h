#ifndef SCN_STEP_BOSS_HITSTOPCALLBACK_H
#define SCN_STEP_BOSS_HITSTOPCALLBACK_H

#include "scn/step/chara/IHitStopCallback.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class HitStopCallback : public chara::IHitStopCallback {
public:
    HitStopCallback(Boss& boss);
    virtual ~HitStopCallback();
    virtual void onStart();
    virtual void onEnd();

private:
    Boss& mBoss;
};

}}}  // namespace scn::step::boss

#endif
