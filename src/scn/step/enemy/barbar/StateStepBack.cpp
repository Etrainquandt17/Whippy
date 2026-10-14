#include "scn/step/enemy/barbar/StateStepBack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/barbar/Custom.h"
#include "scn/step/enemy/barbar/ParamData.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace barbar {

StateStepBack::StateStepBack(Enemy* enemy) : StateBase(enemy), mIsHidden(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().anim().currentG3DAnimIndex() != 3) {
        custom.setStepBackSpeed();
        custom.reqCameraInSoundSE(0x2f0);
    }
    obj().footState().setAir();
    if (obj().kind() == 0x4d && obj().model().anim().currentG3DAnimIndex() == 4 && custom.isHidden()) {
        mIsHidden = true;
        Vector3 velocity = obj().move().velocity();
        velocity *= obj().param().barbar().mHiddenSpeedRate;
        obj().move().setVelocity(velocity);
    } else {
        obj().model().reqScript(9);
    }
}

void StateStepBack::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().isAllEnd() && 0.0f == obj().move().velocity().x && 0.0f == obj().move().velocity().y) {
        if (custom.isHidden()) {
            obj().location().setPos(custom.getInitPos());
        }
        obj().brainCtrl().toValid();
    }
}

void StateStepBack::procMove() {
    f32 size = DynamicCastToRef<Custom, ICustom>(obj().custom()).getSize();
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Zero();
    decel._0 = obj().param().barbar().mStepBackDecel;
    decel._0 *= size;
    if (mIsHidden) {
        decel._0 *= obj().param().barbar().mHiddenDecelRate;
    }
    obj().move().decel(decel);
}

}}}}  // namespace scn::step::enemy::barbar
