#include "scn/step/boss/roah/StateMahoroaMotionStarWait.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateMahoroaMotionStarWait::StateMahoroaMotionStarWait(Boss* boss) : StateBase(boss) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0);
    custom.mahoroaCtrl().getCustom().reqMotionStar();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().brainCtrl().toValid();
}

StateMahoroaMotionStarWait::~StateMahoroaMotionStarWait() {}

void StateMahoroaMotionStarWait::procAnim() {}

void StateMahoroaMotionStarWait::procMove() {
    const Param& param = obj().param().roah();
    obj().move().decel(param.mDecel);
}

void StateMahoroaMotionStarWait::procFixPos() {}

}
}
}
}
