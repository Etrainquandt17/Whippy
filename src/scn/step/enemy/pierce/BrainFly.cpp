#include "scn/step/enemy/pierce/BrainFly.h"

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
#include "scn/step/enemy/pierce/StateFlyAround.h"
#include "scn/step/enemy/pierce/StateFlyPursuit.h"
#include "scn/step/enemy/pierce/StateFlySinCurve.h"
#include "scn/step/enemy/pierce/StateFlyWait.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace pierce {

BrainFly::BrainFly(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFly::onStart() {
    switch (obj().variation()) {
    default:
        obj().stateChanger().setNextState<StateFlyWait, Enemy*>(&obj());
        break;
    case 0xab:
        obj().stateChanger().setNextState<StateFlyAround, Enemy*>(&obj());
        break;
    case 0xac:
        obj().stateChanger().setNextState<StateFlyPursuit, Enemy*>(&obj());
        break;
    case 0xaa:
        obj().stateChanger().setNextState<StateFlySinCurve, Enemy*>(&obj());
        break;
    }
    return true;
}

bool BrainFly::onRecover() {
    return onStart();
}

}
}
}
}
