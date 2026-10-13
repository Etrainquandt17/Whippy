#include "scn/step/enemy/landiasingle/StateDeadEnd.h"

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
#include "scn/step/enemy/landiasingle/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

StateDeadEnd::StateDeadEnd(Enemy* enemy) : StateBase(enemy) {
    const ParamData& param = obj().param().landiasingle();
    obj().model().reqScript(0x15);
    obj().move().resetVelocity();
    hel::math::Vector3 pos = obj().location().pos();
    pos.y -= param.mDeadEndOffsetY;
    obj().location().setPos(pos);
    obj().soundSE().start(0x47d);
    switch (static_cast<u32>(obj().level())) {
    case 0:
        obj().target().setIsRightDir(true);
        break;
    case 1:
        obj().target().setIsRightDir(true);
        break;
    case 2:
        obj().target().setIsRightDir(true);
        break;
    case 3:
        obj().target().setIsRightDir(false);
        break;
    }
}

StateDeadEnd::~StateDeadEnd() {}

void StateDeadEnd::procAnim() {}

void StateDeadEnd::procMove() {}

void StateDeadEnd::procFixPos() {}

}
}
}
}
