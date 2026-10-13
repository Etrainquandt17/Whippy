#include "scn/step/hero/interference/StateHang.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hang.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/InterferenceParam.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Nururi.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/hero/common/StateJump.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StateWait.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace interference {

namespace {

struct Vector3Words {
    u32 words[3];
};

}

bool StateHang::TryToChangeState(Hero* hero) {
    if (!hero->hang().isHangNow() && hero->hang().isExistParent() && hero->hang().canHang()) {
        hero->stateChanger().setNextState<StateHang, Hero*>(hero);
        return true;
    }
    return false;
}

StateHang::StateHang(Hero* hero)
    : StateBase(hero)
    , mConstraintPos()
    , mRootPos()
    , mRate(0.0f)
    , _24(0.0f)
    , _28(false) {
    obj().footState().setAir();
    obj().move().resetVelocity();
    obj().model().script().start(0x46);
    obj().hang().setIsHangNow(true);
    obj().hang().setCanReceive(true);
    obj().mapColl().setValid(false);
    obj().nururi().setValid(false);
    obj().wearBack().setBack();
    hel::math::Vector3 pos = obj().hang().getConstraintPos() - obj().hang().getConstraintOffsetChild()
        + hel::math::Vector3(0.0f, -0.3f, 0.0f);
    obj().effect().get_8().requestPD(static_cast<effect::Kind>(0xA0), pos + hel::math::Vector3(0.2f, 0.0f, 1.0f), hel::math::Direction3::BASIS);
    obj().effect().get_8().requestPD(static_cast<effect::Kind>(0xA0), pos + hel::math::Vector3(-0.2f, 0.0f, 1.0f), hel::math::Direction3::BASIS);
    mRootPos = obj().hang().getRootPos();
}

StateHang::~StateHang() {
    obj().hang().unlinkParent();
    obj().hang().unlinkChild();
    obj().nururi().setValid(true, 0x14);
    obj().mapColl().setValid(true);
    obj().hang().setCanReceive(false);
    obj().hang().setIsHangNow(false);
    obj().hang().setInterval(0x1E);
}

void StateHang::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (common::StateLogout::TryToChangeState(objPtr()) || common::StateJump::TryToChangeState(objPtr())) {
        return;
    }
}

void StateHang::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateHang::procConstraint() {
    if (!obj().hang().isExistParent()) {
        release();
        return;
    }
    obj().mapColl().setTriggerPassThroughLand();
    mRootPos = obj().hang().getRootPos();
    obj().target().setIsRightDir(obj().hang().isParentRightDir());
    f32 rot = obj().hang().getParentRotH();
    if (hel::math::Math::AbsF32(rot) > 50.0f) {
        rot = 50.0f * (rot < 0.0f ? -1 : 1);
    }
    obj().model().modelRotCtrl().setRotH(rot * obj().model().getSign());
    mRate += obj().param().interference()._1A4;
    if (mRate > 1.0f) {
        mRate = 1.0f;
    }
    hel::math::Vector3 pos = obj().location().pos();
    mConstraintPos = obj().hang().getConstraintPos();
    pos = pos * (1.0f - mRate) + mConstraintPos * mRate;
    obj().location().setPos(pos);
    hel::math::Vector3 prevPos = obj().location().pos();
    obj().location().setPos(obj().hang().getRootPos());
    obj().mapColl().setValid(true);
    obj().location().setPos(prevPos);
    obj().mapColl().procMapColl();
    obj().mapColl().setValid(false);
    obj().worldCage().proc();
}

void StateHang::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
    if (common::StateWait::TryToChangeStateWithScript(objPtr(), static_cast<ScriptKind>(3))) {
        obj().hang().unlinkParent();
        return;
    }
    if (obj().hang().isExistParent()) {
        if (hel::math::Math::Equals(mRate, 1.0f, 0.00001f)) {
            hel::math::Vector3 pos = obj().location().pos();
            // TODO: the copy of the difference stands in for the compiler's own copy, as in Vector3::squareDistance.
            Vector3Words diff = reinterpret_cast<const Vector3Words&>(static_cast<const hel::math::Vector3&>(pos - mConstraintPos));
            f32 length = hel::math::Math::SqrtF(reinterpret_cast<const hel::math::Vector3&>(diff).squareLength());
            if (length > obj().param().interference()._1A0) {
                obj().hang().unlinkParent();
            }
        }
    }
}

void StateHang::release() {
    hel::math::Vector3 pos = obj().location().pos();
    obj().location().setPos(mRootPos);
    obj().mapColl().setValid(true);
    obj().location().setPos(pos);
    obj().mapColl().procMapColl();
    Utility::ChangeStateWaitOrFall(obj());
}

}
}
}
}
