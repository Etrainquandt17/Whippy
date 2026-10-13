#include "scn/step/boss/roah/StateStar.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateStar::StateStar(Boss* boss, Config config) : StateBase(boss) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    switch (static_cast<u32>(config._0)) {
    case 1:
        obj().model().reqScript(7);
        break;
    case 3:
        obj().model().reqScript(8);
        break;
    case 5:
        obj().model().reqScript(9);
        break;
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
}

StateStar::~StateStar() {}

void StateStar::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateStar::procMove() {
    const Param& param = obj().param().roah();
    obj().move().decel(param.mDecel);
}

void StateStar::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
