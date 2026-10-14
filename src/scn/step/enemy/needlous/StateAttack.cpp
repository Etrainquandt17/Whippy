#include "scn/step/enemy/needlous/StateAttack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/needlous/Custom.h"
#include "scn/step/enemy/needlous/ParamData.h"
#include "scn/step/enemy/needlous/StateIdling.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;

namespace scn {
namespace step {
namespace enemy {
namespace needlous {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(7);
    obj().brainCtrl().toValid();
}

StateAttack::~StateAttack() {
    obj().move().resetSpeedH();
}

void StateAttack::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().variation() == 0x1b) {
        custom.updateMoveCount();
    }
}

void StateAttack::procMove() {
    const ParamData& param = obj().param().needlous();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().footState().isAir()) {
        obj().move().airDecelFall(param.mDecel, param.mFall);
    }
    obj().move().groundAccel(obj().target().isRightDir(), param.mAttackAccel);
    custom.runSE();
}

void StateAttack::procFixPos() {
    const ParamData& param = obj().param().needlous();
    chara::MapCollResult result = obj().mapColl().result();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (result.mIsHitFloor) {
        if (obj().footState().isAir()) {
            f32 speed = obj().move().velocity().y;
            speed *= param.mAttackBoundRate;
            if (Math::Abs(speed) < param.mAttackBoundMin) {
                speed = 0.0f;
            }
            obj().move().setSpeedV(-speed);
            obj().footState().setGround();
            custom.runSE();
        }
    } else {
        obj().footState().setAir();
    }
    bool isCliff = false;
    if (obj().cliffChecker().isCliff() && obj().footState().isGround()) {
        isCliff = true;
    }
    if (result._2 || Utility::ChkNururiByDir(obj(), 0.1f) || isCliff || custom.isMaxMoveCountOver()) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
        obj().soundSE().start(0x2c1);
        custom.resetMoveCount(false);
        custom.setIdlingTurn(true);
        obj().stateChanger().setNextState<StateIdling, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::needlous
