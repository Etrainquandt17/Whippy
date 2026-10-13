#include "scn/step/enemy/nruff/BrainGrandLowper.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Culling.h"
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
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/nruff/StateFall.h"
#include "scn/step/enemy/nruff/StateGrandLowperAppear.h"
#include "scn/step/enemy/nruff/StateWalk.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace nruff {

BrainGrandLowper::BrainGrandLowper(Enemy& enemy) : BrainBase(enemy) {}

bool BrainGrandLowper::onStart() {
    obj().culling().setHeight(12.0f);
    obj().stateChanger().setNextState<StateGrandLowperAppear, Enemy*>(&obj());
    return true;
}

bool BrainGrandLowper::onLanding() {
    obj().stateChanger().setNextState<StateWalk, Enemy*>(&obj());
    return true;
}

bool BrainGrandLowper::onRecover() {
    obj().model().reqScript(3);
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::nruff
