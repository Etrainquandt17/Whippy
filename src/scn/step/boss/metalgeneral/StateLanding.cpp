#include "scn/step/boss/metalgeneral/StateLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateLanding::StateLanding(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(2);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().move().resetVelocity();
}

StateLanding::~StateLanding() {}

void StateLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateLanding::procMove() {}

void StateLanding::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
