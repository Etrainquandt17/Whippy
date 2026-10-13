#include "scn/step/boss/roah/StateAnger.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/info/BossPanel.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateAnger::StateAnger(Boss* boss) : StateBase(boss), mCount(0), mStartPos(), mGoalPos() {
    const Param& param = obj().param().roah();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(24);
    custom.mahoroaCtrl().getCustom().reqMotionAnger();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().guard().setType(GUARD_TYPE_6);
    obj().infoBossPanel().transformStart();
    custom.rotCtrl().toInvalid();
    {
        g3d::NodeAccessor node = obj().model().model().nodes().at(1);
        hel::math::Vector3 rot(0.0f, param.mRotYMax * obj().target().getSign(), 0.0f);
        node.localMtx().setRTMtx(hel::math::Matrix34::CreateRotXYZDeg(rot));
    }
    mStartPos = obj().location().pos().getXY();
    mGoalPos = obj().basePos();
}

StateAnger::~StateAnger() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).rotCtrl().toValid();
    obj().infoBossPanel().transformEnd();
}

void StateAnger::procAnim() {
    const Param& param = obj().param().roah();
    if (mCount < param.mAngerFrame) {
        mCount++;
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateAnger::procMove() {
    const Param& param = obj().param().roah();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mAngerFrame);
    f32 rate = hel::math::Math::SinDegF(90.0f * t);
    obj().location().setPos(hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, rate).toVector3());
}

void StateAnger::procFixPos() {}

}
}
}
}
