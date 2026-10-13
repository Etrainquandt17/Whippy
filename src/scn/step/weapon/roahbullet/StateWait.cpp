#include "scn/step/weapon/roahbullet/StateWait.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahbullet/Custom.h"
#include "scn/step/weapon/roahbullet/Param.h"
#include "scn/step/weapon/roahbullet/StateMove.h"
#include "scn/step/weapon/roahbullet/StateMoveUp.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

StateWait::StateWait(Weapon* weapon) : StateBase(weapon), mFrame(0), mWaitFrame(0), mRot(0.0f) {
    const Param& param = obj().param().roahBullet();
    mWaitFrame = param._18 + param._1C * hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).waitNum();
    obj().move().resetVelocity();
    g3d::NodeAccessor node = obj().model().model().nodes().at(3);
    hel::math::Matrix34 mtx = node.localMtx().rtMtx();
    mtx.setT(hel::math::Vector3(0.0f, 0.0f, param._10));
    node.localMtx().setRTMtx(mtx);
}

StateWait::~StateWait() {
    obj().model().model().nodes().at(3).localMtx().reset();
}

void StateWait::procAnim() {
    const Param& param = obj().param().roahBullet();
    if (mFrame < mWaitFrame) {
        mFrame++;
    } else {
        if (obj().variation() == 2) {
            obj().stateChanger().setNextState<StateMoveUp, Weapon*>(&obj());
        } else {
            obj().stateChanger().setNextState<StateMove, Weapon*>(&obj());
        }
        return;
    }
    mRot += param._14;
    obj().model().model().nodes().at(2).localMtx().setRTMtx(
        hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(mRot, 0.0f, 0.0f))
    );
}

void StateWait::procMove() {}

void StateWait::procFixPos() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).procFixPos();
}

}}}}  // namespace scn::step::weapon::roahbullet
