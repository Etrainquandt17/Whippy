#include "scn/step/enemy/fattybufferjr/StateAppearFall.h"

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
#include "scn/step/chara/WorldCage.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/fattybufferjr/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferjr {

StateAppearFall::StateAppearFall(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().nururi().setValid(false);
    obj().nururi().setCanNururi(false);
    obj().worldCage().setIsValid(true);
}

void StateAppearFall::procAnim() {
    obj().nururi().setValid(true);
    obj().nururi().setCanNururi(true);
}

void StateAppearFall::procMove() {
    obj().move().airDecelFall(obj().param().fattybufferjr().mAppear.mDecel, obj().param().fattybufferjr().mAppear.mFall);
}

void StateAppearFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::fattybufferjr
