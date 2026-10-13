#include "scn/step/enemy/SuperStop.h"

#include "scn/step/Component.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ObjStop.h"
#include "scn/step/spstop/Manager.h"

namespace scn {
namespace step {
namespace enemy {

SuperStop::SuperStop(Enemy& enemy) : mObj(enemy), mIsSpecial(false) {
    mObj.comp().superStopManager().registerEventReceiver(*this);
}

SuperStop::~SuperStop() {
    mObj.comp().superStopManager().unregisterEventReceiver(*this);
}

void SuperStop::onObjCollReactHit() {
    if (mObj.comp().superStopManager().isStopped()) {
        mObj.objStop().setSpecial();
        mIsSpecial = true;
    }
}

void SuperStop::onSuperStopStarted(const spstop::Manager&) {
    mIsSpecial = false;
}

void SuperStop::onSuperStopFinished(const spstop::Manager&) {
    if (mIsSpecial) {
        mObj.objStop().unsetSpecial();
        mIsSpecial = false;
    }
}

}}}  // namespace scn::step::enemy
