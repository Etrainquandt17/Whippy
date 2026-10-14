#include "scn/step/hero/common/StateSquat.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/LandConstraint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/gimmick/Manager.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateCarryItemCatch.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateSliding.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateWait.h"
#include "util/StateChanger.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateSquat::TryToChangeState(Hero* hero) {
    if (hero->stateChecker().isBombDanger()) {
        return false;
    }
    if (hero->mapColl().result().mIsHitFloor && hero->hid().isHold(4)) {
        hero->stateChanger().setNextState<StateSquat, Hero*>(hero);
        return true;
    }
    return false;
}

StateSquat::StateSquat(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setGround();
    obj().stateChecker().setSquat(true);
    obj().model().script().start(9);
}

StateSquat::~StateSquat() {
    obj().stateChecker().setSquat(false);
}

void StateSquat::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (StateCarryItemPut::TryToChangeState(objPtr()) || StateCarryItemThrow::TryToChangeState(objPtr()) ||
        obj().abilityManager().tryToChangeState() || StateVacuum::TryToChangeState(objPtr()) ||
        StateSliding::TryToChangeState(objPtr()) || StateCarryItemCatch::TryToChangeState(objPtr())) {
        return;
    }
    if (!obj().hid().isHold(4) || obj().stateChecker().isBombDanger()) {
        obj().stateChanger().setNextState<StateWait, Hero*, ScriptKind>(objPtr(), static_cast<ScriptKind>(10));
        return;
    }
    if (mFrame < obj().param().common()._18) {
        mFrame++;
        return;
    }
    if (!obj().mapColl().is_86()) {
        return;
    }
    obj().mapColl().setTriggerPassThroughLand();
    if (obj().mapColl().precheck(Vector2(0.0f, -0.1f)).mIsHitFloor) {
        obj().mapColl().resetTriggerPassThroughLand();
        return;
    }
    obj().move().setSpeedH(obj().move().velocity().x + obj().landConstraint().prevVelocity().x);
    obj().move().setSpeedV(-0.025f);
    obj().stateChanger().setNextState<StateFall, Hero*>(objPtr());
    if (obj().isMainPlayer()) {
        obj().comp().gimmickManager().onThroughLand(static_cast<const Hero&>(obj()).location().pos());
    }
}

void StateSquat::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateSquat::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Hero*>(objPtr());
    }
}

}}}}  // namespace scn::step::hero::common
