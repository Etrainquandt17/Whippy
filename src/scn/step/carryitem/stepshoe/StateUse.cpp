#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/carryitem/stepshoe/StateUse.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Model.h"
#include "gobj/NodeRepos.h"
#include "ocoll/Owner.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/carryitem/stepshoe/StateFall.h"
#include "scn/step/carryitem/stepshoe/Utility.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"

namespace scn {
namespace step {
namespace carryitem {
namespace stepshoe {

StateUse::StateUse(CarryItem* carryItem, f32 flashAngle)
    : StateBase(carryItem)
    , mUseAlgorithm(*carryItem, 0xE9, 0x10C)
    , _34(false)
    , _35(false)
    , mFlashAngle(flashAngle) {
    mUseAlgorithm.setOffset(hel::math::Vector3::ZERO);
    obj().getUser()->resetStepShoeInfo();
    setScale();
    obj().model().procFixPos();
    reqEffect();
    Utility::SetFlash(obj());
    mFlashAngle = Utility::UpdateBodyFlash(obj(), mFlashAngle);
}

StateUse::~StateUse() {
    obj().model().setScale(hel::math::Vector3::ALL_ONE);
}

void StateUse::procAnim() {
    mUseAlgorithm.procAnim();
    if (Utility::ChkLifeTime(obj())) {
        return;
    }
    switch (obj().model().getCurrentScriptIndex()) {
    case 0:
        if (obj().model().isAllEnd()) {
            reqScript(SCRIPT_KIND_JUMP_LOW);
        }
        break;
    case 3:
        if (obj().model().isAllEnd()) {
            reqScript(SCRIPT_KIND_JUMP_HIGH);
        }
        break;
    case 4:
        if (obj().model().isAllEnd()) {
            reqScript(SCRIPT_KIND_JUMP_HIGHT_FALL);
        }
        break;
    }
    Utility::SetFlash(obj());
    Utility::ReqFlashEffect(obj());
    mFlashAngle = Utility::UpdateBodyFlash(obj(), mFlashAngle);
}

void StateUse::procMove() {
    mUseAlgorithm.procMove();
}

void StateUse::procConstraint() {
    if (mUseAlgorithm.procConstraint()) {
        reqEffect();
        obj().stateChanger().setNextState<StateFall, CarryItem*, f32>(objPtr(), mFlashAngle);
        return;
    }
    if (obj().getUser().wasSet()) {
        obj().model().setScale(obj().getUser()->getStepShoeScale());
        obj().model().procFixPos();
    }
    if (obj().getUser().wasSet()) {
        if (obj().getUser()->_53) {
            reqScript(SCRIPT_KIND_ENPTY_WAIT);
        } else if (obj().getUser()->_51) {
            reqScript(SCRIPT_KIND_JUMP_LOW_START);
            _34 = false;
        } else if (obj().getUser()->_52) {
            reqScript(SCRIPT_KIND_JUMP_HIGHT_START);
            _34 = true;
        } else if (obj().getUser()->_55) {
            reqScript(SCRIPT_KIND_FALL_HIT);
            _34 = false;
        } else if (obj().getUser()->_54) {
            if (_34) {
                reqScript(SCRIPT_KIND_JUMP_HIGHT_LANDING);
            } else {
                reqScript(SCRIPT_KIND_JUMP_LOW_END);
            }
        }
        obj().getUser()->resetStepShoeInfo();
    }
}

void StateUse::setScale() {
    // TODO: the original tests the pointer in place here and calls wasSet() in procConstraint.
    if (obj().getUser().operator->() == 0) {
        return;
    }
    if (_35) {
        obj().model().model().nodes().at(2).localMtx().setScale(hel::math::Vector3::ALL_ONE);
        return;
    }
    util::ObjRefHandle<hero::Hero> hero =
        obj().comp().heroManager().searchHeroFromObjCollOwnerID(obj().getUser()->getOCOwner().uid());
    if (!hero.isNull()) {
        hero::AbilityKind kind = hero->abilityManager().abilityKind();
        const Param& param = obj().param().stepShoe();
        f32 rate = param._4;
        switch (kind) {
        case 0x20:
            rate = param._8;
            break;
        case 0x21:
            rate = param._C;
            break;
        case 0x22:
            rate = param._10;
            break;
        }
        hel::math::Vector3 scale = hel::math::Vector3::ALL_ONE;
        scale *= rate;
        obj().model().model().nodes().at(2).localMtx().setScale(scale);
    }
}

void StateUse::reqEffect() {
    hel::math::Vector3 pos = obj().model().model().nodes().at(1).worldTrans();
    obj().effect().requestP(static_cast<effect::Kind>(0x9F), pos, 0.85f);
    obj().effect().requestP(static_cast<effect::Kind>(0xB4), pos, 0.7f);
}

void StateUse::reqScript(ScriptKind kind) {
    obj().model().reqScript(kind);
    obj().model().procFixPos();
    _35 = kind == SCRIPT_KIND_ENPTY_WAIT;
    setScale();
}

}}}}  // namespace scn::step::carryitem::stepshoe
