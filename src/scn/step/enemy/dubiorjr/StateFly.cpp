#include "scn/step/enemy/dubiorjr/StateFly.h"

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
#include "scn/step/enemy/dubiorjr/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace dubiorjr {

StateFly::StateFly(Enemy* enemy, f32 rot) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().model().rotCtrl().setRotVTarget(rot * obj().target().getSign());
    obj().brainCtrl().toValid();
}

StateFly::~StateFly() {}

void StateFly::procAnim() {}

void StateFly::procMove() {
    const ParamData& param = obj().param().dubiorjr();
    obj().move().decel(param.mDecel);
}

void StateFly::procFixPos() {}

}
}
}
}
