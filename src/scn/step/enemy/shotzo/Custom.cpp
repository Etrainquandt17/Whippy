#include "scn/step/enemy/shotzo/Custom.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/shotzo/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mAimAngle(0.0f) {}

bool Custom::onInit() {
    obj().captureReceiver().setCanCapture(false);
    obj().target().setIsRightDir(false);
    if (obj().variation() == 0xaf || obj().variation() == 0xb0 || obj().variation() == 0x139) {
        obj().mapColl().setValid(false);
    }
    return false;
}

bool Custom::onInWater() {
    obj().soundSE().start(0x2F6);
    return false;
}

f32 Custom::aimAngle() const {
    return mAimAngle;
}

void Custom::setAimAngle(f32 angle) {
    mAimAngle = angle;
    g3d::NodeAccessor node = obj().model().model().nodes().at(1);
    hel::math::Matrix34 rotX =
        hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3(1.0f, 0.0f, 0.0f), hel::math::Math::Abs(angle));
    node.localMtx().setRTMtx(rotX);
    f32 rot = angle >= 45.0f ? 90.0f : (angle <= -45.0f ? -90.0f : 2.0f * angle);
    hel::math::Matrix34 rotY = hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3(0.0f, 1.0f, 0.0f), rot);
    if (obj().variation() == 0xaf || obj().variation() == 0xb0 || obj().variation() == 0x139) {
        hel::math::Matrix34 rotZ = hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3(0.0f, 0.0f, 1.0f), 180.0f);
        hel::math::Matrix34 up = hel::math::Matrix34::CreateTrans(hel::math::Vector3(0.0f, 0.5f, 0.0f));
        hel::math::Matrix34 down = hel::math::Matrix34::CreateTrans(hel::math::Vector3(0.0f, -0.5f, 0.0f));
        obj().model().setCustomMtx(up * rotY * rotZ * down);
    } else {
        obj().model().setCustomMtx(rotY);
    }
}

f32 Custom::playerAngle() {
    hel::math::Vector2 diff = Utility::GetNearestPlayerPos(obj());
    diff -= obj().location().pos().getXY();
    f32 angle = hel::math::Math::Atan2DegF(diff.x, hel::math::Math::Abs(diff.y));
    return hel::math::Math::LimitMinMax(angle, -90.0f, 90.0f);
}

bool Custom::isPlayerInAimArea() {
    f32 area;
    f32 angle = mAimAngle;
    area = obj().param().shotzo().mAimArea;
    return hel::math::Math::Abs(playerAngle() - angle) <= area;
}

bool Custom::isFixPos() const {
    bool result = false;
    if (obj().variation() == 0xaf || obj().variation() == 0xb0 || obj().variation() == 0x139) {
        result = true;
    }
    return result;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::shotzo
