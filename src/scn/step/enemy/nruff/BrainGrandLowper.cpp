#include "scn/step/enemy/nruff/BrainGrandLowper.h"

#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/nruff/StateFall.h"
#include "scn/step/enemy/nruff/StateGrandLowperAppear.h"
#include "scn/step/enemy/nruff/StateWalk.h"

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
