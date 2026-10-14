#include "scn/step/boss/landia/HeadAngleCtrl.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using g3d::NodeAccessor;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace landia {

HeadAngleCtrl::HeadAngleCtrl(Boss& boss) : mBoss(boss), mNeckAngle(0.0f), mHeadAngle(0.0f), mIsValid(true) {}

void HeadAngleCtrl::update() {
    const Param& param = mBoss.param().landia();
    Vector3 heroPos = Utility::GetHatedHeroPos(mBoss);
    f32 diffY = heroPos.y - (param.mHeadOffsetY + mBoss.location().pos().y);
    f32 neckAngle = Math::LimitMinMax(diffY * param.mNeckAngleRate, param.mNeckAngleMin, param.mNeckAngleMax);
    f32 headAngle = 0.0f;
    if (Math::Equals(neckAngle, param.mNeckAngleMax, 0.00001f) || Math::Equals(neckAngle, param.mNeckAngleMin, 0.00001f)) {
        f32 distance = Math::AbsF32(heroPos.x - mBoss.location().pos().x);
        if (distance < param.mHeadDistance) {
            headAngle = Math::LimitMinMax(param.mHeadAngleRate * (param.mHeadDistance - distance), param.mHeadAngleMin, param.mHeadAngleMax);
            if (neckAngle < 0.0f) {
                headAngle *= -1.0f;
            }
        }
    }
    if (!mIsValid) {
        neckAngle = 0.0f;
        headAngle = 0.0f;
    }
    mNeckAngle = 0.9f * mNeckAngle + 0.1f * neckAngle;
    mHeadAngle = 0.9f * mHeadAngle + 0.1f * headAngle;
    setMtx(NODE_KIND_3, mNeckAngle);
    setMtx(NODE_KIND_4, mNeckAngle);
    setMtx(NODE_KIND_5, mNeckAngle);
    setMtx(NODE_KIND_6, mNeckAngle);
    setMtx(NODE_KIND_11, mHeadAngle);
    setMtx(NODE_KIND_12, mHeadAngle);
    setMtx(NODE_KIND_13, mHeadAngle);
    setMtx(NODE_KIND_14, mHeadAngle);
    setMtx(NODE_KIND_15, mHeadAngle);
    setMtx(NODE_KIND_16, mHeadAngle);
    setMtx(NODE_KIND_17, mHeadAngle);
    setMtx(NODE_KIND_18, mHeadAngle);
}

void HeadAngleCtrl::toValid() {
    mIsValid = true;
}

void HeadAngleCtrl::toInvalid() {
    mIsValid = false;
}

void HeadAngleCtrl::setMtx(NodeKind kind, f32 angle) {
    NodeAccessor node = mBoss.model().model().nodes().at(kind);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(-angle, 0.0f, 0.0f)));
}

}}}}  // namespace scn::step::boss::landia
