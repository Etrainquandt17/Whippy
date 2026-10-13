#include "scn/step/enemy/bouncy/BrainMove.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/bouncy/ParamData.h"
#include "scn/step/enemy/bouncy/StateJump.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    obj().stateChanger().setNextState<StateJump, Enemy*>(&obj());
    Utility::SetTargetByDirType(obj());
    return true;
}

bool BrainMove::onRecover() {
    obj().move().setSpeedH(obj().param().bouncy().mMoveRecoverSpeedH);
    obj().move().setSpeedV(obj().param().bouncy().mMoveRecoverSpeedV);
    return onStart();
}

}
}
}
}
