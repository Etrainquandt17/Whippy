#include "scn/step/enemy/juckle/BrainFollow.h"

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
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/juckle/Custom.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace juckle {

BrainFollow::BrainFollow(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFollow::onStart() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.onFollowFlag();
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

bool BrainFollow::onRecover() {
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

}
}
}
}
