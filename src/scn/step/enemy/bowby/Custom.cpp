#include "scn/step/enemy/bowby/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/DamageInfo.h"
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
#include "scn/step/enemy/bowby/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace bowby {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mAngle(0.0f), mIsAnimStart(false) {
    switch (enemy.dirType()) {
    case 4:
        mAngle = 0.0f;
        obj().model().rotCtrl().initRotV(180.0f);
        break;
    case 5:
        mAngle = -180.0f;
        obj().model().rotCtrl().initRotV(0.0f);
        break;
    case 3:
        mAngle = 90.0f;
        obj().model().rotCtrl().initRotV(90.0f);
        break;
    default:
        mAngle = -90.0f;
        obj().model().rotCtrl().initRotV(270.0f);
        break;
    }
    obj().model().rotCtrl().setValid(false);
}

bool Custom::onHitPointIsZero() {
    if (obj().damageInfo().attackType() == 0x12) {
        return false;
    }
    if (obj().damageInfo().element() == 3) {
        obj().model().rotCtrl().setValid(true);
        obj().model().rotCtrl().resetRot();
    }
    return false;
}

void Custom::onCaptured() {
    obj().model().rotCtrl().setValid(true);
    obj().model().rotCtrl().resetRot();
}

f32 Custom::playerAnger() {
    hel::math::Vector2 playerPos = Utility::GetNearestPlayerPos(obj());
    hel::math::Vector2 pos = obj().location().pos().getXY();
    playerPos -= pos;
    return hel::math::Math::Atan2DegF(playerPos.x, playerPos.y);
}

bool Custom::isPlayerInArea() {
    const ParamData& param = obj().param().bowby();
    bool result;
    f32 angle;
    switch (obj().dirType()) {
    case 4:
        result = true;
        angle = mAngle;
        if (!(hel::math::Math::Abs(playerAnger() - angle) <= param.mAreaNear)) {
            angle = mAngle;
            bool isFar = hel::math::Math::Abs(playerAnger() - angle) >= param.mAreaFar;
            if (!isFar) {
                result = false;
            }
        }
        break;
    case 5:
        result = true;
        angle = mAngle;
        if (!(hel::math::Math::Abs(playerAnger() - angle) <= param.mAreaNear)) {
            angle = mAngle;
            bool isFar = hel::math::Math::Abs(playerAnger() - angle) >= param.mAreaFar;
            if (!isFar) {
                result = false;
            }
        }
        break;
    default:
        Utility::SetTargetByDirType(obj());
        result = Utility::IsHeroInRange(obj(), 8.0f, -8.0f, 0.0f, 9.0f);
        break;
    }
    return result;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

bool Custom::isAnimStart() const {
    return mIsAnimStart;
}

void Custom::setAnimStart(bool start) {
    mIsAnimStart = start;
}

}}}}  // namespace scn::step::enemy::bowby
