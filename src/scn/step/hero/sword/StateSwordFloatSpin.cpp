#include "scn/step/hero/sword/StateSwordFloatSpin.h"
#include "gobj/FootState.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/common/StateJump.h"
#include "scn/step/hero/common/StateWaterFloat.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

bool StateSwordFloatSpin::TryToChangeState(Hero* hero) {
    if (hero->stateChecker().isFloat() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwordFloatSpin, Hero*>(hero);
        return true;
    }
    return false;
}

StateSwordFloatSpin::StateSwordFloatSpin(Hero* hero)
    : StateBase(hero)
    , mIsBubble(true)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().stateChecker().setFloat(true);
    obj().model().script().start(0x8B);
    obj().invincible().set(7);
}

StateSwordFloatSpin::~StateSwordFloatSpin() {
    obj().stateChecker().setFloat(false);
}

void StateSwordFloatSpin::procAnim() {
    if (!obj().water().isOnSurface()) {
        reqJumpEffect();
        obj().stateChanger().setNextState<common::StateJump, Hero*>(objPtr());
        return;
    }
    mFrame++;
    if (obj().model().scriptTrigger().get(0)) {
        mIsBubble = false;
    }
    if (mIsBubble) {
        Utility::RequestBubbleRollAction(obj(), mFrame);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWaterFloat, Hero*>(objPtr());
    }
}

void StateSwordFloatSpin::procMove() {
    const CommonParam& common = obj().param().common();
    Utility::MoveFromKeyState(obj(), common._A8._14, common._A8._10, gobj::MoveParamFall::Zero());
}

void StateSwordFloatSpin::procFixPos() {
}

void StateSwordFloatSpin::reqJumpEffect() {
    hel::math::Vector3 pos = static_cast<const Hero&>(obj()).location().pos();
    pos.y += 0.5f;
    hel::math::Direction3 dir;
    dir.mUp = obj().water().getSurfaceUpVec(pos.getXY());
    dir.restructUpFront();
    obj().effect()._8.requestPD(static_cast<effect::Kind>(0x74), pos, dir);
}

}
}
}
}
