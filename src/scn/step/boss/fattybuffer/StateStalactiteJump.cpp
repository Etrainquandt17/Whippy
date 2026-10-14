#include "scn/step/boss/fattybuffer/StateStalactiteJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateStalactiteLanding.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateStalactiteJump::StateStalactiteJump(Boss* boss, StalactiteJumpKind kind) : StateBase(boss), mKind(kind) {
    const Param& param = obj().param().fattybuffer();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    switch (mKind) {
    case STALACTITE_JUMP_KIND_0:
        obj().model().reqScript(0x24);
        obj().move().setSpeedV(param._13C);
        break;
    case STALACTITE_JUMP_KIND_1:
        obj().model().reqScript(0x27);
        obj().move().setSpeedV(param._14C);
        break;
    case STALACTITE_JUMP_KIND_2:
        obj().model().reqScript(0x2A);
        obj().move().setSpeedV(param._15C);
        break;
    case STALACTITE_JUMP_KIND_3:
        obj().model().reqScript(0x2D);
        obj().move().setSpeedV(param._13C);
        break;
    case STALACTITE_JUMP_KIND_4:
        obj().model().reqScript(0x30);
        obj().move().setSpeedV(param._15C);
        break;
    }
    obj().guard().setType(static_cast<GuardType>(2));
}

StateStalactiteJump::~StateStalactiteJump() {}

void StateStalactiteJump::procAnim() {}

void StateStalactiteJump::procMove() {
    const Param& param = obj().param().fattybuffer();
    gobj::MoveParamFall fall = gobj::MoveParamFall::Zero();
    switch (mKind) {
    case STALACTITE_JUMP_KIND_0:
        fall = param._140;
        break;
    case STALACTITE_JUMP_KIND_1:
        fall = param._150;
        break;
    case STALACTITE_JUMP_KIND_2:
        fall = param._160;
        break;
    case STALACTITE_JUMP_KIND_3:
        fall = param._140;
        break;
    case STALACTITE_JUMP_KIND_4:
        fall = param._160;
        break;
    }
    obj().move().airDecelFall(param._18, fall);
}

void StateStalactiteJump::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().stateChanger().setNextState<StateStalactiteLanding, Boss*, StalactiteJumpKind>(objPtr(), mKind);
    }
}

}}}}  // namespace scn::step::boss::fattybuffer
