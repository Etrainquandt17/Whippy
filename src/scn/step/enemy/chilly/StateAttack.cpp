#include "scn/step/enemy/chilly/StateAttack.h"

#include "gobj/FootState.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/chilly/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace chilly {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().objColl().clearAttack();
}

StateAttack::~StateAttack() {
    obj().objColl().clearAttack();
    obj().soundSE().stop();
}

void StateAttack::procAnim() {
    const ParamData& param = obj().param().chilly();
    mFrame++;
    if (mFrame == param.mAttackScriptFrame) {
        obj().model().reqScript(9);
    }
    if (mFrame == param.mAttackEffectFrame) {
        effect::Kind kind = obj().isSuper() ? static_cast<effect::Kind>(0x309) : static_cast<effect::Kind>(0x301);
        obj().effect().state().requestN(kind, 0);
        obj().soundSE().start(0x2e9);
    }
    if (mFrame == param.mAttackCollFrame) {
        obj().objColl().clearAttack();
        obj().objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x1a6));
        obj().objColl().addAttack(0, 0, param.mAttackRadius, param.mAttackOffset);
    }
    if (mFrame >= param.mAttackEndFrame) {
        obj().brainCtrl().toValid();
        obj().soundSE().stop();
    }
}

void StateAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
