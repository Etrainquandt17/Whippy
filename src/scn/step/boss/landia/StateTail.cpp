#include "scn/step/boss/landia/StateTail.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/boss/landia/StateWait.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateTail::StateTail(Boss* boss, Config config) : StateBase(boss), mCount(0), mStartPos(), mGoalPos(), mIsMove(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    switch (config._0) {
    case 0:
        obj().model().reqScript(22);
        break;
    case 1:
        obj().model().reqScript(28);
        break;
    }
    custom.waftCtrl().setWaveWidthZero();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
}

StateTail::~StateTail() {
    obj().objColl().clearAttack(1);
}

void StateTail::procAnim() {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mCount < param._218) {
        mCount++;
    } else {
        mIsMove = false;
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        reqStar();
    }
    if (obj().scriptTrigger().get(1)) {
        mIsMove = true;
        mCount = 0;
        mStartPos = custom.waftCtrl().getRefPos().getXY();
        mGoalPos = mStartPos;
        f32 distance = 0.0f;
        if (Utility::IsVariationExtra(obj())) {
            distance = param._220;
        } else {
            distance = param._21C;
        }
        f32 sign = obj().target().getSign();
        mGoalPos.x += sign * distance;
    }
}

void StateTail::procMove() {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mIsMove) {
        f32 rate;
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._218);
        rate = 1.0f - (1.0f - hel::math::Math::SinDegF(90.0f * t)) * (1.0f - hel::math::Math::SinDegF(90.0f * t));
        custom.waftCtrl().setRefPos(hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, rate).toVector3());
    }
}

void StateTail::procFixPos() {}

void StateTail::reqStar() {
    const Param& param = obj().param().landia();
    hel::math::Vector2 offset(param._21C * obj().target().getSign(), 0.0f);
    hel::math::Vector2 pos(param._224 * obj().target().getSign(), param._228);
    hel::math::Vector2 speed(param._24 * obj().target().getSign(), param._28);
    Utility::GenerateStarEffect(obj(), pos + offset, speed, map::BinEnemyVariation_StarBound);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0xB4), obj().location().pos() + (offset + pos).toVector3());
    pos.x *= -1.0f;
    speed.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), pos + offset, speed, map::BinEnemyVariation_StarBound);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0xB4), obj().location().pos() + (offset + pos).toVector3());
}

}
}
}
}
