#include "scn/step/enemy/squishy/StateMoveInWater.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/squishy/Custom.h"
#include "scn/step/enemy/squishy/ParamData.h"
#include "scn/step/enemy/squishy/StateFall.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

StateMoveInWater::StateMoveInWater(Enemy* enemy) : StateBase(enemy), mIsInWater(true), mFrame(0), mMoveFrame(0) {
    const ParamData& param = obj().param().squishy();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().move().resetVelocity();
    if (obj().variation() == 0xa0) {
        Utility::TurnHero(obj());
    } else if (obj().variation() == 0x9f) {
        obj().model().rotCtrl().initRotH(0.0f);
        obj().model().rotCtrl().setValid(false);
    }
    if (Utility::GetNearestPlayerPos(obj()).y >= obj().location().pos().y) {
        mMoveFrame = param.mMoveInWaterFrameUp;
    } else {
        mMoveFrame = param.mMoveInWaterFrameDown;
    }
    mIsInWater = custom.isInWater(false);
}

StateMoveInWater::~StateMoveInWater() {
    obj().model().rotCtrl().setValid(true);
}

void StateMoveInWater::procAnim() {
    const ParamData& param = obj().param().squishy();
    if (mIsInWater) {
        mFrame++;
        if (mFrame > mMoveFrame) {
            obj().brainCtrl().toValid();
        }
    } else {
        if (obj().variation() != 0x9f) {
            obj().move().setVelocity(param.mOutWaterVelocity * obj().target().getSign());
        }
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateMoveInWater::procMove() {
    const ParamData& param = obj().param().squishy();
    if (mFrame > param.mMoveInWaterAccelStartFrame) {
        if (obj().variation() == 0x9f) {
            obj().move().airAccelFall(obj().target().isRightDir(), param.mMoveInWaterStayAccel, param.mMoveInWaterStayFall);
        } else {
            obj().move().airAccelFall(obj().target().isRightDir(), param.mMoveInWaterAccel, param.mMoveInWaterFall);
        }
    }
}

void StateMoveInWater::procFixPos() {
    mIsInWater = DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater(false);
    if (obj().mapColl().result().isHitWallFront()) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    Utility::ChkNururiTurn(obj());
}

}}}}  // namespace scn::step::enemy::squishy
