#include "scn/step/enemy/fattybufferjr/StateJump.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mintglue/VectorInline.h"
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
#include "scn/step/enemy/fattybufferjr/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferjr {

StateJump::StateJump(Enemy* enemy, const hel::math::Vector3& velocity) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(8);
    obj().move().setVelocity(velocity);
    obj().target().setIsRightDir(app::Random::RandBool(0.5f));
}

void StateJump::procAnim() {}

void StateJump::procMove() {
    const ParamData::Air& param = obj().param().fattybufferjr().mJump;
    obj().move().airDecelFall(param.mDecel, param.mFall);
}

void StateJump::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}
}
}
}
