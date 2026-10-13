#include "scn/step/enemy/common/StateMahoroa2CallingShotAppear.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateMahoroa2CallingShotShot.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

// TODO: the link dropped every function of this class (nothing in the game sets this state), so their bodies
// are unknown: the map gives 0x11C, 0x7C, 0x200, 0x1A0 and 4 bytes. What the unit keeps is the factory of
// StateMahoroa2CallingShotShot, which shows that one of them sets that state. These bodies stand in for that.
StateMahoroa2CallingShotAppear::StateMahoroa2CallingShotAppear(Enemy* enemy) : StateBase(enemy) {}

StateMahoroa2CallingShotAppear::~StateMahoroa2CallingShotAppear() {}

void StateMahoroa2CallingShotAppear::procAnim() {
    obj().stateChanger().setNextState<StateMahoroa2CallingShotShot, Enemy*>(objPtr());
}

void StateMahoroa2CallingShotAppear::procMove() {}

void StateMahoroa2CallingShotAppear::procFixPos() {}

}
}
}
}
