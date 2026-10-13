#include "scn/step/enemy/mahoroahammer/StateBound.h"

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
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateWait.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroahammer {

StateBound::StateBound(Enemy* enemy, const hel::math::Vector2& velocity) : StateBase(enemy) {
    obj().footState().setAir();
    hel::math::Vector3 v = velocity.toVector3();
    v.x *= obj().target().getSign();
    obj().move().setVelocity(v);
}

StateBound::~StateBound() {}

void StateBound::procAnim() {
    f32 rot = obj().model().rotCtrl().getRotV();
    rot += -12.5f * obj().target().getSign();
    if (rot < 0.0f) {
        rot += 360.0f;
    }
    if (rot >= 360.0f) {
        rot -= 360.0f;
    }
    obj().model().rotCtrl().initRotV(rot);
}

void StateBound::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), obj().param().common().mFall);
}

void StateBound::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<common::StateWait, Enemy*>(objPtr());
    }
}

}
}
}
}
