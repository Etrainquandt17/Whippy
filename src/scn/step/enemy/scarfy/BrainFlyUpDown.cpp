#include "scn/step/enemy/scarfy/BrainFlyUpDown.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/scarfy/Custom.h"
#include "scn/step/enemy/scarfy/StateAngerChase.h"
#include "scn/step/enemy/scarfy/StateFaceChange.h"
#include "scn/step/enemy/scarfy/StateFlyUpDown.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

BrainFlyUpDown::BrainFlyUpDown(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFlyUpDown::onStart() {
    obj().stateChanger().setNextState<StateFlyUpDown, Enemy*>(&obj());
    return true;
}

bool BrainFlyUpDown::onRecover() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isAngerFlag() == true) {
        obj().stateChanger().setNextState<StateAngerChase, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateFaceChange, Enemy*>(&obj());
    }
    return true;
}

}
}
}
}
