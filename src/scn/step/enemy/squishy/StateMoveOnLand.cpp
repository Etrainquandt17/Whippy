#include "scn/step/enemy/squishy/StateMoveOnLand.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/squishy/Custom.h"
#include "scn/step/enemy/squishy/ParamData.h"
#include "scn/step/enemy/squishy/StateFall.h"
#include "scn/step/enemy/squishy/StateJump.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

StateMoveOnLand::StateMoveOnLand(Enemy* enemy) : StateBase(enemy), mFrame(0), mIsInWater(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(7);
    if (obj().variation() == 0xa0) {
        Utility::TurnHero(obj());
    }
    mIsInWater = custom.isInWater(false);
}

StateMoveOnLand::~StateMoveOnLand() {}

void StateMoveOnLand::procAnim() {
    const ParamData& param = obj().param().squishy();
    if (mIsInWater) {
        obj().brainCtrl().toValid();
    } else {
        mFrame += 2;
        if (mFrame == param.mMoveOnLandFrame) {
            obj().stateChanger().setNextState<StateJump, Enemy*>(objPtr());
        }
    }
}

void StateMoveOnLand::procMove() {
    const ParamData& param = obj().param().squishy();
    obj().move().groundAccel(obj().target().isRightDir(), param.mMoveOnLandAccel);
}

void StateMoveOnLand::procFixPos() {
    mIsInWater = DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater(false);
    if (obj().mapColl().result().isHitWallFront()) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    Utility::ChkNururiTurn(obj());
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::squishy
