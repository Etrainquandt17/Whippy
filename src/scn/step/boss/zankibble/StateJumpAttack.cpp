#include "scn/step/boss/zankibble/StateJumpAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/boss/zankibble/Custom.h"
#include "scn/step/boss/zankibble/Param.h"
#include "scn/step/boss/zankibble/ScriptKind.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

StateJumpAttack::StateJumpAttack(Boss* boss, Config config) : StateBase(boss), mIsFall(false), mStartPos(), mTargetPos() {
    obj().footState().setAir();
    obj().model().reqScript(18);
    mStartPos = obj().location().pos().getXY();
    if (config._0) {
        mTargetPos = obj().comp().mainCamera().getCenter();
        bool isRight = mTargetPos.x - mStartPos.x > 0.0f;
        obj().target().setIsRightDir(isRight);
    } else {
        mTargetPos.x = mStartPos.x;
        mTargetPos.y = obj().comp().mainCamera().getCenter().y;
    }
}

StateJumpAttack::~StateJumpAttack() {}

void StateJumpAttack::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        mIsFall = true;
    }
    if (obj().scriptTrigger().get(1)) {
        reqCutterSlant();
    }
}

void StateJumpAttack::procMove() {
    const Param& param = obj().param().zankibble();
    if (mIsFall) {
        obj().move().airDecelFall(param._28, param._2C);
        return;
    }
    if (obj().model().anim().currentG3DAnimIndex() == 19) {
        f32 rate = hel::math::Math::SinDegF(90.0f * (obj().model().anim().frame() / obj().model().anim().totalFrame()));
        hel::math::Vector2 pos = hel::math::Math::LinearInterpolation(mStartPos, mTargetPos, rate);
        pos.y += param.mJumpAttackHeight * hel::math::Math::SinDegF(180.0f * rate);
        obj().location().setPos(pos.toVector3());
    } else {
        obj().move().resetVelocity();
    }
}

void StateJumpAttack::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateLanding, Boss*, ScriptKind>(objPtr(), static_cast<ScriptKind>(21));
    }
}

void StateJumpAttack::reqCutterSlant() {
    const Param& param = obj().param().zankibble();
    hel::math::Vector2 pos = obj().location().pos().getXY();
    pos += hel::math::Vector2(param.mCutterSlantOffset.x * obj().target().getSign(), param.mCutterSlantOffset.y);
    hel::math::Vector3 velocity(param.mCutterSlantSpeed.x * obj().target().getSign(), param.mCutterSlantSpeed.y, 0.0f);
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().request(EnemyCtrl::CUTTER_KIND_SLANT, pos, velocity, false);
}

}
}
}
}
