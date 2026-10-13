#include "scn/step/boss/SoundSE.h"

namespace scn {
namespace step {
namespace boss {

SoundSE::SoundSE() {}

SoundSE::~SoundSE() {
    mState.stop();
    mLoop.stop();
    mNonStop.stop();
}

snd::SERequestor& SoundSE::normal() {
    return mNormal;
}

snd::SERequestor& SoundSE::state() {
    return mState;
}

snd::SERequestor& SoundSE::loop() {
    return mLoop;
}

snd::SERequestor& SoundSE::nonStop() {
    return mNonStop;
}

void SoundSE::onStateChange() {
    mState.stop();
}

void SoundSE::onHitStopStart() {}

void SoundSE::onHitStopEnd() {}

void SoundSE::onObjStopStarted() {
    mNormal.pauseInc();
    mState.pauseInc();
    mLoop.pauseInc();
}

void SoundSE::onObjStopFinished() {
    mLoop.pauseDec();
    mState.pauseDec();
    mNormal.pauseDec();
}

}}}  // namespace scn::step::boss
