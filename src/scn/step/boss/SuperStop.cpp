#include "scn/step/boss/SuperStop.h"

#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/ObjStop.h"
#include "scn/step/spstop/Manager.h"

namespace scn {
namespace step {
namespace boss {

SuperStop::SuperStop(Boss& boss) : mBoss(boss), mIsSpecial(false), mIsStopped(false), mIsAutoSpecial(false) {
    boss.comp().superStopManager().registerEventReceiver(*this);
}

SuperStop::~SuperStop() {
    mBoss.comp().superStopManager().unregisterEventReceiver(*this);
}

void SuperStop::onObjCollReactHit() {
    if (mBoss.comp().superStopManager().isStopped()) {
        setSpecial();
    }
}

void SuperStop::onSuperStopStarted(const spstop::Manager&) {
    mIsStopped = true;
    unsetSpecial();
    if (mIsAutoSpecial) {
        setSpecial();
    }
}

void SuperStop::onSuperStopFinished(const spstop::Manager&) {
    mIsStopped = false;
    unsetSpecial();
}

void SuperStop::setAutoSpecial() {
    mIsAutoSpecial = true;
    if (mIsStopped) {
        setSpecial();
    }
}

void SuperStop::unsetAutoSpecial() {
    mIsAutoSpecial = false;
}

void SuperStop::setSpecial() {
    if (!mIsSpecial) {
        mBoss.objStop().setSpecial();
        mIsSpecial = true;
    }
}

void SuperStop::unsetSpecial() {
    if (mIsSpecial) {
        mBoss.objStop().unsetSpecial();
        mIsSpecial = false;
    }
}

}}}  // namespace scn::step::boss
