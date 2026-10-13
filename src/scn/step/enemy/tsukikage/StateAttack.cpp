#include "scn/step/enemy/tsukikage/StateAttack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/tsukikage/Custom.h"
#include "scn/step/enemy/tsukikage/ParamData.h"
#include "scn/step/enemy/tsukikage/StateFall.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(9);
    Utility::TurnHero(obj());
    if (obj().target().isRightDir()) {
        obj().effect().state().requestN(static_cast<effect::Kind>(0x4a3), 0);
    } else {
        obj().effect().state().requestN(static_cast<effect::Kind>(0x4a2), 0);
    }
}

void StateAttack::procAnim() {
    const ParamData& param = obj().param().tsukikage();
    mFrame++;
    if (mFrame == param.mShurikenFrame + 1) {
        obj().soundSE().start(0x2ee);
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).requestShuriken();
    }
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
