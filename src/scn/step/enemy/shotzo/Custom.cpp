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

using g3d::NodeAccessor;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

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
    NodeAccessor node = obj().model().model().nodes().at(1);
    Matrix34 rotX =
        Matrix34::CreateRotAxisDeg(Vector3(1.0f, 0.0f, 0.0f), Math::Abs(angle));
    node.localMtx().setRTMtx(rotX);
    f32 rot = angle >= 45.0f ? 90.0f : (angle <= -45.0f ? -90.0f : 2.0f * angle);
    Matrix34 rotY = Matrix34::CreateRotAxisDeg(Vector3(0.0f, 1.0f, 0.0f), rot);
    if (obj().variation() == 0xaf || obj().variation() == 0xb0 || obj().variation() == 0x139) {
        Matrix34 rotZ = Matrix34::CreateRotAxisDeg(Vector3(0.0f, 0.0f, 1.0f), 180.0f);
        Matrix34 up = Matrix34::CreateTrans(Vector3(0.0f, 0.5f, 0.0f));
        Matrix34 down = Matrix34::CreateTrans(Vector3(0.0f, -0.5f, 0.0f));
        obj().model().setCustomMtx(up * rotY * rotZ * down);
    } else {
        obj().model().setCustomMtx(rotY);
    }
}

f32 Custom::playerAngle() {
    Vector2 diff = Utility::GetNearestPlayerPos(obj());
    diff -= obj().location().pos().getXY();
    f32 angle = Math::Atan2DegF(diff.x, Math::Abs(diff.y));
    return Math::LimitMinMax(angle, -90.0f, 90.0f);
}

bool Custom::isPlayerInAimArea() {
    f32 area;
    f32 angle = mAimAngle;
    area = obj().param().shotzo().mAimArea;
    return Math::Abs(playerAngle() - angle) <= area;
}

bool Custom::isFixPos() const {
    bool result = false;
    if (obj().variation() == 0xaf || obj().variation() == 0xb0 || obj().variation() == 0x139) {
        result = true;
    }
    return result;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::shotzo
