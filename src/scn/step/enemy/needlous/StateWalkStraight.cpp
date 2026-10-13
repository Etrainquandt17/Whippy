#include "scn/step/enemy/needlous/StateWalkStraight.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/needlous/Custom.h"
#include "scn/step/enemy/needlous/ParamData.h"
#include "scn/step/enemy/needlous/StateIdling.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace needlous {

StateWalkStraight::StateWalkStraight(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    switch (enemy->level()) {
    case 0:
        mAccel = gobj::MoveParamAccel::Create(0.02f, 0.02f, 0.001f);
        break;
    case 1:
        mAccel = gobj::MoveParamAccel::Create(0.03f, 0.03f, 0.001f);
        break;
    case 2:
        mAccel = gobj::MoveParamAccel::Create(0.04f, 0.04f, 0.001f);
        break;
    default:
        mAccel = gobj::MoveParamAccel::Create(0.06f, 0.06f, 0.001f);
        obj().cliffChecker().changeFrontDist(obj().param().common().mCliffFrontDist);
        break;
    }
    obj().footState().setGround();
    obj().model().reqScript(3);
    obj().model().setFrameRate(mAccel._0 / 0.02f);
    obj().brainCtrl().toValid();
}

StateWalkStraight::~StateWalkStraight() {}

void StateWalkStraight::procAnim() {
    const ParamData& param = obj().param().needlous();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().variation() == 0x1b) {
        custom.updateMoveCount();
    }
    mFrame++;
    if (mFrame >= param.mWalkFrame) {
        obj().move().resetSpeedH();
        obj().move().setSpeedV(param.mJumpSpeed);
        obj().soundSE().start(0x2b8);
        custom.setAttack(true);
        if (custom.isMaxMoveCountOver()) {
            obj().target().setIsRightDir(!obj().target().isRightDir());
        }
        custom.resetMoveCount(true);
        obj().stateChanger().setNextState<StateIdling, Enemy*>(objPtr());
    }
}

void StateWalkStraight::procMove() {
    obj().move().groundAccel(obj().target().isRightDir(), mAccel);
}

void StateWalkStraight::procFixPos() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    chara::MapCollResult result = obj().mapColl().result();
    bool isCliff = false;
    if (obj().cliffChecker().isCliff() && obj().footState().isGround()) {
        isCliff = true;
    }
    if (result._2 || isCliff || Utility::ChkNururiByDir(obj(), 0.1f) || custom.isMaxMoveCountOver()) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
        custom.resetMoveCount(false);
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
