#include "scn/step/boss/roah/StateOarEnd.h"

#include "g3d/NodeAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/core/PermEffect.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateOarEnd::StateOarEnd(Boss* boss) : StateBase(boss), mIsTriggered(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(20);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    custom.resetSubAnimOar();
    obj().model().model().nodes().at(12).setVisibilityBelow(true);
}

StateOarEnd::~StateOarEnd() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setSubAnimOar();
    if (!mIsTriggered) {
        for (u32 i = 0; i < 6; i++) {
            hel::math::Vector3 pos = obj().model().model().nodes().at(i + 13).worldTrans();
            obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x7A), pos);
        }
    }
}

void StateOarEnd::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        mIsTriggered = true;
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateOarEnd::procMove() {
    const Param& param = obj().param().roah();
    obj().move().decel(param.mDecel);
}

void StateOarEnd::procFixPos() {}

}
}
}
}
