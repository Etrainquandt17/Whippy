#include "scn/step/hero/supersword/StateAttackFinishWait.h"
#include "gobj/Move.h"
#include "hid/RumbleRequestor.h"
#include "scn/step/chara/LandConstraint.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CaptureHeroReceiver.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/ItemCollReact.h"
#include "scn/step/chara/Knockback.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Nururi.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/super/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace supersword {

StateAttackFinishWait::StateAttackFinishWait(Hero* hero)
    : StateBase(hero) {
    obj().move().resetVelocity();
    obj().model().setFixDir(true);
    obj().abilityManager().lockFuel();
    obj().objColl().setXlu();
    obj().captureHeroReceiver().setCanCapture(false);
    obj().water().setForbidChangeState(true);
    obj().itemCollReact().setForbidChangeAbility(true);
    obj().knockback().setIsValid(false);
    obj().landConstraint().setMode(static_cast<chara::LandConstraint::Mode>(0));
    Utility::SetSecondMoveIsValid(obj(), false);
    super::Utility::UnlinkPiggyBack(obj());
    obj().nururi().setCanNururi(false);
}

StateAttackFinishWait::~StateAttackFinishWait() {
    Utility::SetSecondMoveIsValid(obj(), true);
    obj().itemCollReact().setForbidChangeAbility(false);
    obj().water().setForbidChangeState(false);
    obj().captureHeroReceiver().setCanCapture(true);
    obj().objColl().unsetXlu();
    obj().abilityManager().unlockFuel();
    obj().hidRumble().stop();
}

void StateAttackFinishWait::procAnim() {
}

void StateAttackFinishWait::procMove() {
}

void StateAttackFinishWait::procFixPos() {
}

bool StateAttackFinishWait::procObjCollReact() {
    return false;
}

}}}}  // namespace scn::step::hero::supersword
