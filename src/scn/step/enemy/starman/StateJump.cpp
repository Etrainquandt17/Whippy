#include "scn/step/enemy/starman/StateJump.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
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
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/starman/Custom.h"
#include "scn/step/enemy/starman/ParamData.h"
#include "scn/step/enemy/starman/StateFall.h"
#include "scn/step/ocoll/AttackType.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace starman {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy), mIsEnd(false) {
    const ParamData& param = obj().param().starman();
    mSpeedH = hel::math::Math::AbsF32(obj().move().velocity().x);
    obj().footState().setAir();
    obj().model().reqScript(8);
    mIsHighJump = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isHighJumpMode();
    if (mIsHighJump) {
        obj().move().setSpeedV(param.mHighJumpSpeed);
        obj().effect().state().requestN(static_cast<effect::Kind>(0x2e3), 0);
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x2e4), 0);
        obj().objColl().clearAttack();
        obj().objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x199));
        obj().objColl().addAttack(0, 1, param.mAttackRadius, hel::math::Vector2(0.0f, param.mAttackOffsetY));
        obj().soundSE().start(0x2e6);
    } else {
        obj().move().setSpeedV(param.mJumpSpeed);
        obj().soundSE().start(0x2a9);
    }
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    if (obj().move().velocity().y <= 0.0f && !mIsEnd) {
        obj().effect().state().release();
        obj().objColl().clearAttack();
        mIsEnd = true;
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateJump::procMove() {
    const ParamData& param = obj().param().starman();
    const gobj::MoveParamAccel& accel = gobj::MoveParamAccel::Create(mSpeedH, 1.0f, 0.0f);
    obj().move().airAccelFall(obj().target().isRightDir(), accel, param.mFall);
}

void StateJump::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor && obj().model().anim().frame() >= 1.0f) {
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
    if (obj().mapColl().result().isHitWall()) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
}

}
}
}
}
