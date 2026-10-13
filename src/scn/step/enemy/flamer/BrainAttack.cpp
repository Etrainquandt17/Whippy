#include "scn/step/enemy/flamer/BrainAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
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
#include "scn/step/enemy/flamer/Custom.h"
#include "scn/step/enemy/flamer/StateAgony.h"
#include "scn/step/enemy/flamer/StateChase.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainAttack::onStart() {
    obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    return true;
}

bool BrainAttack::onRecover() {
    if (!hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isAttackEnd()) {
        obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateAgony, Enemy*>(&obj());
    }
    return true;
}

}
}
}
}
