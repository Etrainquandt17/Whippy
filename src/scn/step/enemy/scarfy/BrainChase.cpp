#include "scn/step/enemy/scarfy/BrainChase.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/scarfy/Custom.h"
#include "scn/step/enemy/scarfy/StateAngerChase.h"
#include "scn/step/enemy/scarfy/StateChase.h"
#include "scn/step/enemy/scarfy/StateFaceChange.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

BrainChase::BrainChase(Enemy& enemy) : BrainBase(enemy) {}

bool BrainChase::onStart() {
    obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    return true;
}

bool BrainChase::onRecover() {
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
