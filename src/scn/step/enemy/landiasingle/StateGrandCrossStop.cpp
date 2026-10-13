#include "scn/step/enemy/landiasingle/StateGrandCrossStop.h"

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
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/landiasingle/ParamData.h"
#include "scn/step/enemy/landiasingle/StateGrandCrossEndWait.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

StateGrandCrossStop::StateGrandCrossStop(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().model().reqScript(7);
    obj().move().resetVelocity();
}

StateGrandCrossStop::~StateGrandCrossStop() {}

void StateGrandCrossStop::procAnim() {
    const ParamData& param = obj().param().landiasingle();
    if (mFrame < param.mGrandCrossStopFrame) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateGrandCrossEndWait, Enemy*>(objPtr());
        return;
    }
    if (mFrame % 5 == 0) {
        obj().model().shake().request(static_cast<chara::ShakeKind>(1));
    }
}

void StateGrandCrossStop::procMove() {}

void StateGrandCrossStop::procFixPos() {}

}
}
}
}
