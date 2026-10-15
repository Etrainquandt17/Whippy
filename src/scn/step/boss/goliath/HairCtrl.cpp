#include "scn/step/boss/goliath/HairCtrl.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/GearModel.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/goliath/DynamicsDesc.h"
#include "scn/step/chara/Model.h"

using g3d::NodeAccessor;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

namespace {

enum AnimKind {
    ANIM_HAIR_ANGRY = 0x47,
    ANIM_HAIR_NORMAL = 0x48,
};

}

HairCtrl::HairCtrl(Boss& boss) : mBoss(boss), mIsAngry(false), mPhaseY(0.0f), mPhaseZ(0.0f) {}

void HairCtrl::update() {
    mPhaseY += 55.0f;
    if (mPhaseY >= 360.0f) {
        mPhaseY -= 360.0f;
    }
    f32 ampY = mIsAngry ? 35.0f : 0.0f;
    f32 rotY = ampY * Math::SinDegF(mPhaseY);
    mPhaseZ += 14.0f;
    if (mPhaseZ >= 360.0f) {
        mPhaseZ -= 360.0f;
    }
    f32 ampZ = mIsAngry ? 35.0f : 0.0f;
    f32 rotZ = ampZ * (-0.5f * (1.0f - Math::CosDegF(mPhaseZ)));
    NodeAccessor node = mBoss.model().model().nodes().at(9);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(0.0f, rotY, rotZ)));
}

void HairCtrl::setAngry(bool isAngry) {
    mIsAngry = isAngry;
    const chara::ModelDesc::DynamicsDesc& desc = DynamicsDesc::Create(mIsAngry);
    mBoss.model().changeDynamics(desc);
    AnimKind anim = mIsAngry ? ANIM_HAIR_ANGRY : ANIM_HAIR_NORMAL;
    mBoss.model().anim().subAnimSet(0, anim, 10);
    mBoss.model().anim().subAnimAccessor(0).start(true);
}

}}}}  // namespace scn::step::boss::goliath
