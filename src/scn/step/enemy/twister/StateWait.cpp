#include "scn/step/enemy/twister/StateWait.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
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
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/twister/Custom.h"
#include "scn/step/enemy/twister/ParamData.h"
#include "scn/step/enemy/twister/StateFall.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace twister {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().model().anim().setFrameRate(0.0f);
    obj().footState().setGround();
    obj().brainCtrl().toValid();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const ParamData& param = obj().param().twister();
    if (mFrame <= 4) {
        mFrame++;
    }
    if (mFrame > 4 && custom.getThetaX() < param.mThetaXMax) {
        custom.setThetaX(param.mThetaXMax / 10.0f + custom.getThetaX());
    }
    custom.setThetaY(param.mThetaYSpeed + custom.getThetaY());
    g3d::NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().setRTMtx(hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(custom.getThetaX(), custom.getThetaY(), 0.0f)));
}

void StateWait::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateWait::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
