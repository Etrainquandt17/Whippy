#include "scn/step/hero/beam/StateBeamWhip.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/sfx/DarknessLightSizeKind.h"

namespace scn {
namespace step {
namespace hero {
namespace beam {

StateBeamWhip::StateBeamWhip(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , _C(20.0f)
    , mPushCount(0)
    , mWait(0x19)
    , mPrevFrame(0.0f)
    , mIsEnd(false)
    , mStep(0) {
    obj().model().setFixDir(true);
    obj().model().script().start(0xC0);
    obj().move().resetSpeedV();
    obj().invincible().set(7);
    mIsRight = obj().target().isRightDir();
    obj().abilityManager().setCustomDarknessLightSizeKind(static_cast<sfx::DarknessLightSizeKind>(5));
}

StateBeamWhip::~StateBeamWhip() {
    obj().soundSE()._4.stop();
    obj().soundSE()._78.stop();
}

void StateBeamWhip::procAnim() {
    mFrame++;
    switch (mStep) {
    case 0:
        procAnimWhip();
        break;
    case 1:
        procAnimRevolution();
        break;
    }
}

void StateBeamWhip::procMove() {
    switch (mStep) {
    case 0:
        obj().move().airDecelFall(obj().param().common()._74, gobj::MoveParamFall::Create(0.1f, 0.00075f, 0.005f));
        break;
    case 1:
        obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Zero());
        break;
    }
}

void StateBeamWhip::procFixPos() {
    switch (mStep) {
    case 0:
        Utility::MapCollReactDefaultAction(obj());
        break;
    case 1:
        if (common::StateWait::TryToChangeStateWithScript(objPtr(), static_cast<ScriptKind>(3))) {
            return;
        }
        break;
    }
}

void StateBeamWhip::procAnimWhip() {
    if (mFrame < 0x1B && obj().hid().isTrigger(0x20)) {
        mPushCount++;
        if (obj().footState().isAir() && mPushCount >= 3) {
            mStep = 1;
            obj().model().script().start(0xC5);
            obj().move().resetVelocity();
            obj().invincible().set(7);
            return;
        }
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
        obj().soundSE()._4.stop();
    }
}

void StateBeamWhip::procAnimRevolution() {
    if (!mIsEnd) {
        if (obj().hid().isTrigger(0x20)) {
            mWait = 0x19;
        }
        if (mPrevFrame > obj().model().anim().frame()) {
            obj().move().resetSpeedV();
        }
        mPrevFrame = obj().model().anim().frame();
        if (mWait != 0) {
            mWait--;
        } else {
            mIsEnd = true;
            obj().model().script().start(0xC6);
        }
    } else if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

}
}
}
}
