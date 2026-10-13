#include "scn/step/boss/BrainCtrl.h"

#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/core/MintManager.h"

namespace scn {
namespace step {
namespace boss {

BrainCtrl::BrainCtrl(Boss& boss) : mBoss(boss), mRunner(boss.comp().mintManager().engine()), mIsValid(false), mIsSet(false) {}

void BrainCtrl::update() {
    if (mIsSet && mIsValid) {
        onExecPre();
        mRunner.execute();
        onExecPost();
    }
}

void BrainCtrl::set(const char* name) {
    mRunner.setEntryPoint(name);
    mIsSet = true;
}

void BrainCtrl::toValid() {
    mIsValid = true;
}

void BrainCtrl::toInvalid() {
    mIsValid = false;
}

bool BrainCtrl::isValid() const {
    return mIsValid;
}

void BrainCtrl::onExecPre() {
    Utility::MintRegister(mBoss);
}

void BrainCtrl::onExecPost() {
    Utility::MintUnregister(mBoss);
}

}
}
}
