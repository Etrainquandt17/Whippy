#include "scn/step/enemy/walf/BrainMove.h"

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
#include "scn/step/enemy/walf/StateMoveInWater.h"
#include "scn/step/enemy/walf/StateMoveOnGround.h"
#include "scn/step/enemy/walf/StateMoveOnWater.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace walf {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isInWater()) {
        obj().stateChanger().setNextState<StateMoveInWater, Enemy*>(&obj());
    } else if (custom.isFloating()) {
        obj().stateChanger().setNextState<StateMoveOnWater, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMoveOnGround, Enemy*>(&obj());
    }
    return true;
}

bool BrainMove::onRecover() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater()) {
        obj().stateChanger().setNextState<StateMoveInWater, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMoveOnGround, Enemy*>(&obj());
    }
    return true;
}

}}}}  // namespace scn::step::enemy::walf
