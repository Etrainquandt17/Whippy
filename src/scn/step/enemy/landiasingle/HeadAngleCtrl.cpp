#include "scn/step/enemy/landiasingle/HeadAngleCtrl.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/landiasingle/ParamData.h"

using g3d::NodeAccessor;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

HeadAngleCtrl::HeadAngleCtrl(Enemy& enemy) : mObj(enemy), mAngleX(0.0f), mAngleY(0.0f), mIsValid(true) {}

void HeadAngleCtrl::update() {
    const ParamData& param = mObj.param().landiasingle();
    Vector3 playerPos = Utility::GetNearestPlayerPos(mObj).toVector3();
    f32 height = playerPos.y - (param._14 + mObj.location().pos().y);
    f32 angleX = Math::LimitMinMax(height * param._18, param._20, param._1c);
    f32 angleY = 0.0f;
    if (Math::Equals(angleX, param._1c, 0.00001f) || Math::Equals(angleX, param._20, 0.00001f)) {
        f32 distance = Math::AbsF32(playerPos.x - mObj.location().pos().x);
        if (distance < param._24) {
            angleY = Math::LimitMinMax(param._28 * (param._24 - distance), param._30, param._2c);
            if (angleX < 0.0f) {
                angleY *= -1.0f;
            }
        }
    }
    if (!mIsValid) {
        angleX = 0.0f;
        angleY = angleX;
    }
    mAngleX = 0.9f * mAngleX + 0.1f * angleX;
    mAngleY = 0.9f * mAngleY + 0.1f * angleY;
    setMtx(NODE_KIND_HEAD, mAngleX);
    setMtx(NODE_KIND_EYE_L, mAngleY);
    setMtx(NODE_KIND_EYE_R, mAngleY);
}

void HeadAngleCtrl::toValid() {
    mIsValid = true;
}

void HeadAngleCtrl::toInvalid() {
    mIsValid = false;
}

void HeadAngleCtrl::setMtx(NodeKind kind, f32 angle) {
    NodeAccessor node = mObj.model().model().nodes().at(kind);
    Vector3 rot(-angle, 0.0f, 0.0f);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(rot));
}

}}}}  // namespace scn::step::enemy::landiasingle
