#include "scn/step/enemy/sirkibble/StateCatch.h"

#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/sirkibble/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

StateCatch::StateCatch(Enemy* enemy) : StateBase(enemy) {
    obj().model().reqScript(8);
}

StateCatch::~StateCatch() {}

void StateCatch::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    }
}

void StateCatch::procMove() {}

void StateCatch::procFixPos() {}

}}}}  // namespace scn::step::enemy::sirkibble
