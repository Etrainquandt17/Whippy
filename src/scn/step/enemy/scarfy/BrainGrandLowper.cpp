#include "scn/step/enemy/scarfy/BrainGrandLowper.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/scarfy/Custom.h"
#include "scn/step/enemy/scarfy/StateAngerChase.h"
#include "scn/step/enemy/scarfy/StateFaceChange.h"
#include "scn/step/enemy/scarfy/StateGrandLowperAppear.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

BrainGrandLowper::BrainGrandLowper(Enemy& enemy) : BrainBase(enemy) {}

bool BrainGrandLowper::onStart() {
    obj().stateChanger().setNextState<StateGrandLowperAppear, Enemy*>(&obj());
    return true;
}

bool BrainGrandLowper::onRecover() {
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
