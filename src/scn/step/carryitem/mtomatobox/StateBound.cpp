#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/carryitem/mtomatobox/StateBound.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Location.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/Color.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/arena/Manager.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/Flash.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/Utility.h"
#include "scn/step/carryitem/mtomatobox/Param.h"
#include "scn/step/carryitem/mtomatobox/StateUse.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/SoundSE.h"
#include "scn/step/chara/Water.h"
#include "scn/step/item/Desc.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/Manager.h"
#include "scn/step/map/KindUtil.h"

extern "C" double fmod(double, double);

namespace scn {
namespace step {
namespace carryitem {
namespace mtomatobox {

namespace {

const Param& param(CarryItem& carryItem) {
    return carryItem.param().mtomatoBox();
}

}

StateBound::StateBound(CarryItem* carryItem)
    : StateBase(carryItem)
    , mFallAlgorithm(*carryItem, 0xF9)
    , mBoundAlgorithm(*carryItem, 0xF9)
    , mIsWait(false)
    , mIsCrashed(false)
    , mWaitFrame(0)
    , mFlashAngle(0.0f)
    , mBoundCount(0) {
    obj().mapColl().setValid(true);
    mBoundAlgorithm.setSpeedV(param(obj())._10);
    mBoundAlgorithm.setReduceV(param(obj())._14);
    mBoundAlgorithm.setRateH(param(obj())._18);
    obj().model().reqScript(0);
    hel::math::Vector3 velocity = obj().move().velocity() * 0.7f;
    obj().move().setVelocity(velocity);
    mFallAlgorithm.setRotSpeedRate(0.7f);
}

StateBound::~StateBound() {
    obj().mapColl().setValid(false);
    obj().move().resetMoveRate();
}

void StateBound::procAnim() {
    mFallAlgorithm.procAnim();
}

void StateBound::procMove() {
    if (obj().water().isInWater()) {
        mFallAlgorithm.procMove();
    } else {
        obj().move().airDecelFall(
            gobj::MoveParamDecel::Create(param(obj())._0),
            gobj::MoveParamFall::Create(param(obj())._8, param(obj())._4, param(obj())._C));
    }
}

void StateBound::procFixPos() {
    if (isChangeWait()) {
        mIsWait = true;
        mFallAlgorithm.setIsBounded(true);
        obj().move().resetVelocity();
        obj().setIsEnableCarry(true);
    }
    if (mIsCrashed) {
        if (obj().model().anim().isAnimEnd()) {
            obj().dead();
        }
        return;
    }
    if (mIsWait) {
        mWaitFrame++;
        if (obj().footState().isGround()) {
            flash();
        }
        u32 frame = mWaitFrame;
        if (frame > param(obj())._24) {
            if (frame % 4 == 0) {
                obj().model().shake().request(static_cast<chara::ShakeKind>(1));
            }
        } else if (frame % 6 == 0) {
            obj().model().shake().request(static_cast<chara::ShakeKind>(0));
        }
        if (mWaitFrame > param(obj())._20) {
            crash();
            return;
        }
    }
    if (obj().getUser().wasSet()) {
        obj().stateChanger().setNextState<StateUse, CarryItem*>(objPtr());
        return;
    }
    if (mIsWait) {
        mFallAlgorithm.procFixPos();
    } else {
        mBoundAlgorithm.procFixPos();
    }
    if (mBoundAlgorithm.isBound()) {
        obj().effectBack().requestP(static_cast<effect::Kind>(0xA0), obj().location().pos());
        obj().effectBack().requestP(static_cast<effect::Kind>(0xA0), obj().location().pos());
        mBoundAlgorithm.setIsBound(false);
        mBoundCount++;
    }
}

void StateBound::procObjCollReact() {
    mFallAlgorithm.procObjCollReact();
}

bool StateBound::isChangeWait() {
    if (mIsWait) {
        return false;
    }
    if (!obj().mapColl().result().isHitFloor()) {
        return false;
    }
    if (obj().water().isInWater()) {
        return true;
    }
    return mBoundCount >= param(obj())._28;
}

void StateBound::crash() {
    obj().model().reqScript(1);
    obj().effectBack().requestP(static_cast<effect::Kind>(0x34F), obj().location().pos());
    obj().soundSE().start(0x108);
    Utility::OnCrash(obj());
    item::Desc desc(static_cast<map::BinItemKind>(2), 0, true, static_cast<map::BinItemVariation>(1), obj().location().pos().getXY());
    util::ObjRefHandle<item::Item> item = obj().comp().itemManager().request(desc);
    if (!item.isNull()) {
        item->culling().setValid(false);
    }
    mIsCrashed = true;
    if (obj().kind() == 2 && obj().comp().arenaManager().isArena() && map::KindUtil::IsArenaStage(obj().comp().context().mapKind)) {
        obj().comp().arenaManager().setBoxState(static_cast<scn::arena::ArenaData::BoxState>(1));
    }
}

void StateBound::flash() {
    f32 t = 0.5f * (static_cast<f32>(mWaitFrame) / static_cast<f32>(param(obj())._20)) + 0.5f;
    mFlashAngle += 30.0f;
    mFlashAngle = fmod(mFlashAngle, 360.0);
    f32 cos = hel::math::Math::CosDegF(mFlashAngle);
    f32 rate = 1.5f * t + t * (-0.5f * t * t);
    u8 alpha = static_cast<u8>(256.0f * (0.5f * (1.0f - cos)) * rate);
    obj().flash().set(hel::common::Color(0xFF, 0xFF, 0xFF, alpha));
}

}}}}  // namespace scn::step::carryitem::mtomatobox
