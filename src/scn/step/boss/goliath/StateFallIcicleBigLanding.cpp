#include "scn/step/boss/goliath/StateFallIcicleBigLanding.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateWait.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateFallIcicleBigLanding::StateFallIcicleBigLanding(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(0x2A);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateFallIcicleBigLanding::~StateFallIcicleBigLanding() {}

void StateFallIcicleBigLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateFallIcicleBigLanding::procMove() {}

void StateFallIcicleBigLanding::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
