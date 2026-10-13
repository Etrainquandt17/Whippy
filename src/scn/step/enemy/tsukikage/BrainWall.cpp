#include "scn/step/enemy/tsukikage/BrainWall.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/tsukikage/StateFall.h"
#include "scn/step/enemy/tsukikage/StateWall.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

BrainWall::BrainWall(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWall::onStart() {
    obj().stateChanger().setNextState<StateWall, Enemy*>(&obj());
    return true;
}

bool BrainWall::onRecover() {
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::tsukikage
