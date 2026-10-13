#ifndef SCN_STEP_BOSS_SOUNDSE_H
#define SCN_STEP_BOSS_SOUNDSE_H

#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace boss {

class SoundSE {
public:
    SoundSE();
    ~SoundSE();

    snd::SERequestor& normal();
    snd::SERequestor& state();
    snd::SERequestor& loop();
    snd::SERequestor& nonStop();
    void onStateChange();
    void onHitStopStart();
    void onHitStopEnd();
    void onObjStopStarted();
    void onObjStopFinished();

private:
    snd::SERequestor mNormal;
    snd::SERequestor mState;
    snd::SERequestor mLoop;
    snd::SERequestor mNonStop;
};

}}}  // namespace scn::step::boss

#endif
