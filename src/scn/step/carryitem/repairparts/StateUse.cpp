#include "scn/step/carryitem/repairparts/StateUse.h"

#include "gobj/Location.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/carryitem/repairparts/StateRepairThrow.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/SoundSE.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace carryitem {
namespace repairparts {

StateUse::StateUse(CarryItem* carryItem)
    : StateBase(carryItem)
    , mIsRightDir(false)
    , mIsVisible(false)
    , mFrameCounter() {
    obj().mapColl().setValid(false);
    obj().model().setVisibility(false);
    obj().effect().requestPause();
    obj().effectBack().requestPause();
    obj().effectWarp().requestPause();
    if (obj().getUser().operator->() != 0) {
        mIsRightDir = obj().getUser()->isRightDir();
    }
    mFrameCounter.reset(200);
}

StateUse::~StateUse() {
    obj().mapColl().setValid(true);
}

void StateUse::procAnim() {
    mFrameCounter.advanceIfNotEnd();
    if (mFrameCounter.isEnd() && !mIsVisible) {
        mIsVisible = true;
        obj().model().setVisibility(true);
        obj().effect().requestUnpause();
        obj().effectBack().requestUnpause();
        obj().effectWarp().requestUnpause();
        obj().model().reqScript(0);
    }
}

void StateUse::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Create(0.25f, 0.01f, 0.005f));
}

void StateUse::procFixPos() {
    if (obj().getUser().operator->() == 0) {
        obj().soundSE().start(0xFE);
        Vector3 velocity(
            obj().param().repairparts()._0, obj().param().repairparts()._4, obj().param().repairparts()._8);
        velocity.x *= mIsRightDir ? 1.0f : -1.0f;
        obj().move().setVelocity(velocity);
        obj().stateChanger().setNextState<StateRepairThrow, CarryItem*>(objPtr());
    } else {
        obj().location().setPos(obj().getUser()->getConstraintPos());
        mIsRightDir = obj().getUser()->isRightDir();
        obj().model().updateMtx();
    }
}

}}}}  // namespace scn::step::carryitem::repairparts
