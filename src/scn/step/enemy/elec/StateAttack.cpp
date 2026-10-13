#include "scn/step/enemy/elec/StateAttack.h"

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
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/elec/ParamData.h"
#include "scn/step/enemy/elec/StateChase.h"
#include "scn/step/ocoll/AttackType.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace elec {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0.0f) {
    obj().model().reqScript(10);
    obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x1a2));
}

StateAttack::~StateAttack() {
    obj().objColl().bodyColl().unsetAttackTypeOver();
}

void StateAttack::procAnim() {
    f32 end = static_cast<f32>(obj().param().elec().mAttackEndFrame);
    mFrame += 1.0f;
    if (mFrame > end) {
        obj().stateChanger().setNextState<StateChase, Enemy*>(objPtr());
    }
}

}
}
}
}
