#include "scn/step/enemy/common/BrainFlushPursuit.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFlushWait.h"
#include "scn/step/enemy/common/StatePursuit.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

BrainFlushPursuit::BrainFlushPursuit(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFlushPursuit::onStart() {
    obj().stateChanger().setNextState<StateFlushWait, Enemy*>(&obj());
    return true;
}

bool BrainFlushPursuit::onRecover() {
    obj().stateChanger().setNextState<StatePursuit, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::common
