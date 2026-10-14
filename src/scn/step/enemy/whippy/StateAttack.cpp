#include "scn/step/enemy/whippy/StateAttack.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateWait.h"
#include "scn/step/enemy/whippy/ParamData.h"

using g3d::NodeAccessor;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace whippy {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0), mAngle(0.0f) {
    obj().model().reqScript(7);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    aimAntenna(0.0f);
}

StateAttack::~StateAttack() {
    aimAntenna(0.0f);
}

void StateAttack::procAnim() {
    const ParamData& param = obj().param().whippy();
    if (mFrame == param.mAimFrame) {
        NodeAccessor node = obj().model().model().nodes().at(1);
        Vector2 diff = Utility::GetNearestPlayerPos(obj());
        diff -= node.worldMtx().getT().getXY();
        mAngle = Math::Atan2DegF(diff.x, diff.y);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWait, Enemy*>(objPtr());
    } else {
        mFrame++;
        if (mFrame > param.mReturnFrame) {
            mAngle *= 0.8f;
        }
    }
    if (mFrame > param.mAntennaFrame) {
        aimAntenna(mAngle);
    }
}

void StateAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

void StateAttack::aimAntenna(f32 angle) {
    const ParamData& param = obj().param().whippy();
    NodeAccessor node = obj().model().model().nodes().at(1);
    Matrix34 mtx = Matrix34::CreateRotAxisDeg(
        Vector3(0.0f, 1.0f, 0.0f), Math::LimitMinMax(angle, -param.mAngleMax, param.mAngleMax));
    mtx.setT(node.localMtx().rtMtx().getT());
    node.localMtx().setRTMtx(mtx);
}

}}}}  // namespace scn::step::enemy::whippy
