#include "scn/step/boss/fattybuffer/StateSwellBalloonMove.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateSwellBalloonBound.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/WorldCage.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateSwellBalloonMove::StateSwellBalloonMove(Boss* boss, u32 count) : StateBase(boss), mCount(count) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0x1D);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_6);
    obj().guard().setType(static_cast<GuardType>(4));
    obj().flash().guard().setIsValid(true);
}

StateSwellBalloonMove::~StateSwellBalloonMove() {}

void StateSwellBalloonMove::procAnim() {}

void StateSwellBalloonMove::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateSwellBalloonMove::procFixPos() {
    if (obj().mapColl().result().isHitWall() || obj().worldCage().getCorrectedDiff().x * obj().target().getSign() < 0.0f) {
        obj().stateChanger().setNextState<StateSwellBalloonBound, Boss*, StateSwellBalloonBound::Kind, u32>(
            objPtr(), StateSwellBalloonBound::KIND_WALL, mCount);
    } else if (obj().mapColl().result().isHitRoof() || obj().worldCage().getCorrectedDiff().y < 0.0f) {
        obj().stateChanger().setNextState<StateSwellBalloonBound, Boss*, StateSwellBalloonBound::Kind, u32>(
            objPtr(), StateSwellBalloonBound::KIND_ROOF, mCount);
    } else if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateSwellBalloonBound, Boss*, StateSwellBalloonBound::Kind, u32>(
            objPtr(), StateSwellBalloonBound::KIND_FLOOR, mCount);
    }
}

}}}}  // namespace scn::step::boss::fattybuffer
