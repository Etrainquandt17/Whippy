#include "scn/step/weapon/SuperStop.h"

#include "scn/step/Component.h"
#include "scn/step/spstop/Manager.h"
#include "scn/step/weapon/ObjStop.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {

SuperStop::SuperStop(Weapon& weapon) : mObj(weapon), mIsBornInStop(weapon.comp().superStopManager().isStopped()), mIsSpecial(false) {
    mObj.comp().superStopManager().registerEventReceiver(*this);
}

SuperStop::~SuperStop() {
    mObj.comp().superStopManager().unregisterEventReceiver(*this);
}

void SuperStop::onObjCollReactHit() {
    if (!mIsSpecial && mObj.comp().superStopManager().isStopped()) {
        mObj.objStop().setSpecial();
        mIsSpecial = true;
    }
}

void SuperStop::onSuperStopStarted(const spstop::Manager&) {
    mIsSpecial = false;
    if (mIsBornInStop) {
        mObj.objStop().setSpecial();
        mIsBornInStop = false;
        mIsSpecial = true;
    }
}

void SuperStop::onSuperStopFinished(const spstop::Manager&) {
    if (mIsSpecial) {
        mObj.objStop().unsetSpecial();
        mIsSpecial = false;
    }
}

}
}
}
