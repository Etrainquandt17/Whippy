#include "scn/step/enemy/mahoroamagicball/StateHomingFollow.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/mahoroamagicball/Custom.h"
#include "scn/step/enemy/mahoroamagicball/ParamData.h"
#include "scn/step/enemy/mahoroamagicball/StateHomingShot.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

namespace {

const ParamData::Follow& t_param(const Enemy& enemy) {
    return Utility::IsExtra(enemy) ? enemy.param().mahoroamagicball().mHomingExtra : enemy.param().mahoroamagicball().mHoming;
}

}

StateHomingFollow::StateHomingFollow(Enemy* enemy) : StateBase(enemy), mAngle(0.0f), mRadius(0.0f) {
    if (!DynamicCastToRef<Custom, ICustom>(obj().custom()).isOwnerAlive()) {
        obj().dead();
        return;
    }
    obj().footState().setAir();
    obj().nururi().setValid(false);
    obj().mapColl().setValid(false);
    obj().model().reqScript(7);
    mAngle = 120.0f * static_cast<f32>(obj().level());
}

StateHomingFollow::~StateHomingFollow() {
    obj().mapColl().setValid(true);
}

void StateHomingFollow::procAnim() {
    if (obj().signal().isValid()) {
        u32 signal = obj().signal().get();
        obj().signal().clear();
        if (signal == 1) {
            obj().stateChanger().setNextState<StateHomingShot, Enemy*>(objPtr());
            return;
        }
    }
    const ParamData::Follow& param = t_param(obj());
    mAngle += param.mAngleSpeed;
    if (mAngle >= 360.0f) {
        mAngle -= 360.0f;
    }
    mRadius += param.mRadiusSpeed;
    if (mRadius > param.mRadiusMax) {
        mRadius = param.mRadiusMax;
    }
}

void StateHomingFollow::procMove() {}

void StateHomingFollow::procConstraint() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isOwnerAlive()) {
        Vector3 pos = custom.owner()->location().pos();
        pos.y += t_param(obj()).mOffsetY;
        pos.z = 0.0f;
        pos.x += mRadius * Math::CosDegF(mAngle);
        pos.z += mRadius * Math::SinDegF(mAngle);
        pos.y -= 0.4f * (mRadius * Math::SinDegF(mAngle));
        obj().location().setPos(pos);
    }
}

void StateHomingFollow::procFixPos() {}

}}}}  // namespace scn::step::enemy::mahoroamagicball
