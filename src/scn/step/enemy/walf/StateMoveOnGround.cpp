#include "scn/step/enemy/walf/StateMoveOnGround.h"

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
#include "scn/step/enemy/walf/Custom.h"
#include "scn/step/enemy/walf/ParamData.h"
#include "scn/step/enemy/walf/StateFall.h"
#include "scn/step/enemy/walf/StateMoveInWater.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace walf {

StateMoveOnGround::StateMoveOnGround(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(3);
}

void StateMoveOnGround::procAnim() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater()) {
        obj().stateChanger().setNextState<StateMoveInWater, Enemy*>(objPtr());
    }
}

void StateMoveOnGround::procMove() {
    obj().move().groundAccel(obj().target().isRightDir(), obj().param().walf().mGroundAccel);
}

void StateMoveOnGround::procFixPos() {
    if (obj().mapColl().result()._2) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    Utility::ChkNururiTurn(obj());
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::walf
