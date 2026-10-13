#include "scn/step/hero/common/StateWaterFloat.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/GroundChecker.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/ItemCatcher.h"
#include "scn/step/hero/Kiss.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/NinjaParam.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/common/StateCarryItemCatchFloat.h"
#include "scn/step/hero/common/StateCarryItemThrowFloat.h"
#include "scn/step/hero/common/StateJump.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/common/StateWaterPistolFloat.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateWaterFloat::StateWaterFloat(Hero* hero)
    : StateBase(hero)
    , mIsMove(false)
    , mFrame(8)
    , mIsNinja(false) {
    obj().footState().setAir();
    obj().stateChecker().setFloat(true);
    if (Utility::IsPressHDirKey(obj())) {
        obj().model().script().start(0x22);
        obj().effect()._58.requestN(static_cast<effect::Kind>(0xB5), 2);
        mIsMove = true;
    } else {
        obj().model().script().start(0x21);
    }
    mIsNinja = obj().abilityManager().abilityKind() == ABILITY_KIND_NINJA;
    if (mIsNinja) {
        obj().model().weapon().model().changeParentNode(0xF);
        obj().model().weapon().setVisibility(true);
        const NinjaParam& param = obj().param().ninja();
        obj().itemCatcher().setSize(hel::math::Vector2(0.0f, param._B4), param._B0);
        updateNinjaViewOffset();
    }
    obj().move().resetSpeedV();
    obj().piggyback().unlinkAll();
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
}

StateWaterFloat::~StateWaterFloat() {
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_NINJA) {
        obj().model().weapon().model().changeParentNode(obj().model().weapon().defaultParentNodeIndex());
        obj().model().weapon().setVisibility(false);
    }
    obj().stateChecker().setFloat(false);
    obj().runChecker().cancelContinue();
    obj().itemCatcher().resetSize();
    obj().model().resetViewOffset();
}

void StateWaterFloat::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (mIsNinja && obj().abilityManager().abilityKind() != ABILITY_KIND_NINJA) {
        mIsNinja = false;
        obj().model().script().start(obj().model().script().currentScriptIndex());
        obj().itemCatcher().resetSize();
        obj().model().resetViewOffset();
    }
    updateNinjaViewOffset();
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) || StateCarryItemThrowFloat::TryToChangeState(objPtr()) ||
        obj().abilityManager().tryToChangeState() || StateWaterPistolFloat::TryToChangeState(objPtr()) ||
        StateLadder::TryToChangeState(objPtr()) || StateCarryItemCatchFloat::TryToChangeState(objPtr())) {
        return;
    }
    if (mFrame != 0) {
        mFrame--;
    }
    if (obj().hid().isTrigger(0x10) || obj().hid().isTrigger(8)) {
        reqJumpEffect();
        obj().stateChanger().setNextState<StateJump, Hero*, u32, bool, bool>(objPtr(), 12, true, true);
        return;
    }
    if (!obj().water().isOnSurface()) {
        reqJumpEffect();
        obj().stateChanger().setNextState<StateJump, Hero*>(objPtr());
        return;
    }
    if (mIsMove) {
        if (!Utility::IsPressHDirKey(obj())) {
            obj().model().script().start(0x21);
            obj().effect()._58.release();
            mIsMove = false;
        }
    } else if (Utility::IsPressHDirKey(obj())) {
        obj().model().script().start(0x22);
        obj().effect()._58.requestN(static_cast<effect::Kind>(0xB5), 2);
        mIsMove = true;
    }
    if (obj().hid().isHold(4)) {
        f32 speed = obj().param().common()._F4;
        obj().move().setSpeedV(-speed);
    }
    if (obj().stateChecker().isCarryBombDanger()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateWaterFloat::procMove() {
    const CommonParamWater water = obj().param().common()._A8;
    Utility::MoveFromKeyState(obj(), water._14, water._10, gobj::MoveParamFall::Zero());
}

void StateWaterFloat::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
    if (obj().footState().isGround()) {
        reqJumpEffect();
        obj().stateChanger().setNextState<StateWait, Hero*>(objPtr());
    }
}

void StateWaterFloat::reqJumpEffect() {
    Utility::ReqWaterFloatOutProduce(obj());
}

void StateWaterFloat::updateNinjaViewOffset() {
    if (!mIsNinja) {
        return;
    }
    if (!obj().groundChecker().isFloorValid()) {
        return;
    }
    f32 floorY = obj().groundChecker().getFloorPos().y;
    f32 y = hel::math::Math::LimitMin(0.4f - (obj().location().pos().y - floorY), 0.0f);
    obj().model().setViewOffset(hel::math::Vector3(0.0f, y, 0.0f));
}

}
}
}
}
