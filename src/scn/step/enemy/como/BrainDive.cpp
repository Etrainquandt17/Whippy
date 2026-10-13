#include "scn/step/enemy/como/BrainDive.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/como/Custom.h"
#include "scn/step/enemy/como/StateBack.h"
#include "scn/step/enemy/como/StateCutFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

BrainDive::BrainDive(Enemy& enemy) : BrainBase(enemy) {}

bool BrainDive::onStart() {
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).threadCtrl().setLength(0.0f);
    return true;
}

bool BrainDive::onRecover() {
    if (!hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).threadCtrl().isCut()) {
        obj().stateChanger().setNextState<StateBack, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateCutFall, Enemy*>(&obj());
    }
    return true;
}

}
}
}
}
