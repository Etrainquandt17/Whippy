#include "scn/step/enemy/bladeknight/BrainWalk.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/bladeknight/Custom.h"
#include "scn/step/enemy/bladeknight/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

BrainWalk::BrainWalk(Enemy& enemy) : BrainBase(enemy) {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).walkFlagOn();
}

bool BrainWalk::onStart() {
    obj().stateChanger().setNextState<StateWalk, Enemy*>(&obj());
    return true;
}

bool BrainWalk::onLanding() {
    return onStart();
}

}
}
}
}
