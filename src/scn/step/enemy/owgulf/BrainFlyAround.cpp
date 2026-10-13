#include "scn/step/enemy/owgulf/BrainFlyAround.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
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
#include "scn/step/enemy/owgulf/ParamData.h"
#include "scn/step/enemy/owgulf/StateFlyStraight.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

BrainFlyAround::BrainFlyAround(Enemy& enemy) : BrainBase(enemy), mBaseX(enemy.location().pos().x) {}

bool BrainFlyAround::onStart() {
    obj().stateChanger().setNextState<StateFlyStraight, Enemy*>(&obj());
    return true;
}

bool BrainFlyAround::onRecover() {
    return onStart();
}

void BrainFlyAround::update() {
    const ParamData& param = obj().param().owgulf();
    if (obj().location().pos().x > mBaseX + param.mAroundDist && obj().target().isRightDir()) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(false);
    } else if (obj().location().pos().x < mBaseX - param.mAroundDist && !obj().target().isRightDir()) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(true);
    }
}

}
}
}
}
