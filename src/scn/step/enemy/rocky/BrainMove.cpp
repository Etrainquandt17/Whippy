#include "scn/step/enemy/rocky/BrainMove.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/rocky/Custom.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    obj().stateChanger().setNextState<common::StateFall, Enemy*>(&obj());
    return true;
}

bool BrainMove::onRecover() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setFallSpeedUp(false);
    return onStart();
}

}
}
}
}
