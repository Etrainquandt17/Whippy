#include "scn/step/enemy/hothead/Custom.h"

#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/damage/StateDeadInWater.h"
#include "scn/step/enemy/hothead/ParamData.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::geo::Rect;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace hothead {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    if (!obj().isSuper()) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x18e), 2);
    }
    return false;
}

bool Custom::onHitPointIsZero() {
    obj().effect().state().releaseAndVanish();
    return false;
}

bool Custom::onVacuumReceive() {
    obj().effect().state().releaseAndVanish();
    return false;
}

bool Custom::onDamaged() {
    obj().effect().state().releaseAndVanish();
    return false;
}

bool Custom::onInWater() {
    obj().effect().state().releaseAndVanish();
    obj().stateChanger().setNextState<damage::StateDeadInWater, Enemy*>(&obj());
    return true;
}

void Custom::onCaptured() {
    obj().effect().state().releaseAndVanish();
}

void Custom::setupSuperEnemyEffect() {
    Vector3 center = obj().location().toCenter();
    obj().effect().super().requestN(static_cast<effect::Kind>(0x132), 0, center);
    obj().effect().super().requestN(static_cast<effect::Kind>(0x190), 4);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x191), 2);
}

bool Custom::isPlayerPosNear() {
    f32 playerX = Utility::GetNearestPlayerPos(obj()).x;
    f32 diff = playerX - obj().location().pos().x;
    if (Math::AbsF32(diff) <= obj().param().hothead().mNearDist) {
        return true;
    }
    return false;
}

bool Custom::isInViewRect() {
    Rect rect = obj().comp().mainCamera().getViewRect();
    Vector2 pos = obj().location().pos().getXY();
    if (rect._8 <= pos.x && pos.x <= rect._C && rect._4 <= pos.y && pos.y <= rect._0) {
        return true;
    }
    return false;
}

int Custom::setAfterAttackFrame() {
    const ParamData& param = obj().param().hothead();
    switch (obj().level()) {
    case 0:
        return param.mAfterAttackFrame[0];
    case 1:
        return param.mAfterAttackFrame[1];
    default:
        return param.mAfterAttackFrame[2];
    }
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::hothead
