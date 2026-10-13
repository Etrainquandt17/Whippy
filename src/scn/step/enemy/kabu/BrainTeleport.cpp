#include "scn/step/enemy/kabu/BrainTeleport.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/kabu/StateTeleport.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

BrainTeleport::BrainTeleport(Enemy& enemy) : BrainBase(enemy) {}

bool BrainTeleport::onStart() {
    Utility::SetTargetByDirType(obj());
    obj().stateChanger().setNextState<StateTeleport, Enemy*>(&obj());
    return true;
}

}
}
}
}
