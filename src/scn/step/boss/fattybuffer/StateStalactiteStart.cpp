#include "scn/step/boss/fattybuffer/StateStalactiteStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateStalactiteJump.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateStalactiteStart::StateStalactiteStart(Boss* boss, StalactiteJumpKind kind) : StateBase(boss), mKind(kind) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    switch (mKind) {
    case STALACTITE_JUMP_KIND_0:
        obj().model().reqScript(0x23);
        break;
    case STALACTITE_JUMP_KIND_1:
        obj().model().reqScript(0x26);
        break;
    case STALACTITE_JUMP_KIND_2:
        obj().model().reqScript(0x29);
        break;
    case STALACTITE_JUMP_KIND_3:
        obj().model().reqScript(0x2C);
        break;
    case STALACTITE_JUMP_KIND_4:
        obj().model().reqScript(0x2F);
        break;
    }
    obj().guard().setType(static_cast<GuardType>(2));
}

StateStalactiteStart::~StateStalactiteStart() {}

void StateStalactiteStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateStalactiteJump, Boss*, StalactiteJumpKind>(objPtr(), mKind);
    }
}

void StateStalactiteStart::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateStalactiteStart::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
