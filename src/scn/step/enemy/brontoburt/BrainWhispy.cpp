#include "scn/step/enemy/brontoburt/BrainWhispy.h"

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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/brontoburt/StateWhispyAppear.h"
#include "scn/step/enemy/common/StateWalkStraight.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

BrainWhispy::BrainWhispy(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWhispy::onStart() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1c4));
    obj().stateChanger().setNextState<StateWhispyAppear, Enemy*>(&obj());
    return true;
}

bool BrainWhispy::onLanding() {
    obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::brontoburt
