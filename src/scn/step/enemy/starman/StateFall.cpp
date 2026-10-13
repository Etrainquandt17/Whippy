#include "scn/step/enemy/starman/StateFall.h"

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
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/starman/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace starman {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(1);
    obj().model().rotCtrl().setValid(false);
}

StateFall::~StateFall() {
    obj().model().rotCtrl().setValid(true);
}

void StateFall::procMove() {
    const ParamData& param = obj().param().starman();
    const gobj::MoveParamAccel& accel = gobj::MoveParamAccel::Zero();
    obj().move().airAccelFall(obj().target().isRightDir(), accel, param.mFall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
    if (obj().mapColl().result().isHitWall()) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
}

}}}}  // namespace scn::step::enemy::starman
