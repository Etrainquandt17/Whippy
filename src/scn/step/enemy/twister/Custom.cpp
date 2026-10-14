#include "scn/step/enemy/twister/Custom.h"

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
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "snd/SERequestor.h"

using g3d::NodeAccessor;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace twister {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mThetaX(0.0f), mThetaY(0.0f) {}

bool Custom::onInit() {
    mThetaX = 0.0f;
    mThetaY = 0.0f;
    obj().model().anim().setFrameRate(1.0f);
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(mThetaX, mThetaY, 0.0f)));
    return false;
}

bool Custom::onHitPointIsZero() {
    return onInit();
}

bool Custom::onVacuumReceive() {
    return onInit();
}

bool Custom::onDamaged() {
    return onInit();
}

void Custom::onCaptured() {
    onInit();
}

void Custom::onDead() {
    onInit();
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

f32 Custom::getThetaX() const {
    return mThetaX;
}

void Custom::setThetaX(f32 theta) {
    mThetaX = theta;
}

f32 Custom::getThetaY() const {
    return mThetaY;
}

void Custom::setThetaY(f32 theta) {
    mThetaY = theta;
}

}}}}  // namespace scn::step::enemy::twister
