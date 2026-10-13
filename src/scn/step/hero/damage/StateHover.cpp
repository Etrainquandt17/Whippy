#include "scn/step/hero/damage/StateHover.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/DamageFlash.h"
#include "scn/step/hero/Hat.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/damage/Utility.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

StateHover::StateHover(Hero* hero)
    : StateBase(hero) {
    obj().footState().setAir();
    obj().stateChecker().setHover(true);
    obj().model().script().start(0x49);
    Utility::InitTarget(obj());
    Utility::InitVelocity(obj());
    obj().hat().setHover();
    if (obj().objColl().objColl().bodyColl().hit().isCollide()) {
        ocoll::Element element =
            static_cast<ocoll::Element>(obj().objColl().objColl().bodyColl().damageInfo().data().mElement);
        obj().damageFlash().set(element);
    }
}

StateHover::~StateHover() {
    obj().hat().setNormal();
    obj().damageFlash().unset();
    obj().stateChecker().setHover(false);
}

void StateHover::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateHover, Hero*, bool>(objPtr(), true);
    }
}

void StateHover::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.001f), obj().param().common()._90);
}

void StateHover::procFixPos() {}

}}}}  // namespace scn::step::hero::damage
