#include "scn/step/enemy/degout/StateFly.h"

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
#include "scn/step/enemy/degout/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace degout {

StateFly::StateFly(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().brainCtrl().toValid();
}

void StateFly::procAnim() {
    mFrame++;
    if (mFrame == obj().param().degout()._3c[6]) {
        obj().model().reqScript(4);
    }
}

}}}}  // namespace scn::step::enemy::degout
