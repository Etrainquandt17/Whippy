#include "scn/step/hero/bomb/StateSwing.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/BombParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/bomb/GearBombController.h"
#include "scn/step/hero/common/StateRun.h"
#include "std/tr1/reference_wrapper.h"
#include "util/StateChanger.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace hero {
namespace bomb {

bool StateSwing::TryToChangeState(Hero* hero, GearBombController& controller) {
    if (hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwing, Hero*, std::tr1::reference_wrapper<GearBombController> >(
            hero, std::tr1::ref(controller));
        return true;
    }
    return false;
}

StateSwing::StateSwing(Hero* hero, GearBombController& controller)
    : StateBase(hero)
    , mController(controller)
    , mFrame(0) {
    obj().model().setFixDir(true);
    if (!controller.isHave()) {
        mController.haveBomb();
    }
    obj().model().subAnimControl().setLiftUpRHand(false);
    Utility::AirAttackInitSpeedV(obj());
    if (obj().footState().isGround()) {
        obj().effect()._8.requestN(static_cast<effect::Kind>(0xAB), 0);
    }
    obj().model().script().start(0x113);
}

StateSwing::~StateSwing() {
    if (mController.isHave()) {
        mController.putBomb();
    }
    obj().runChecker().setAirContinue();
    if (Utility::IsPressHDirKey(obj())) {
        obj().runChecker().setGroundContinue();
    }
}

void StateSwing::procAnim() {
    if (mController.isHave() && obj().model().scriptTrigger().get(0)) {
        const BombParam& param = obj().param().bomb();
        Vector2 speed(param._74 * obj().target().getSign(), param._78);
        Vector2 pos = static_cast<const Hero&>(obj()).location().pos().getXY() + speed;
        mController.swingBomb(pos);
    }
    if (obj().model().isAllEnd()) {
        if (common::StateRun::TryToChangeState(objPtr())) {
            return;
        }
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSwing::procMove() {
    obj().move().airDecelFall(obj().param().bomb()._7C, obj().param().bomb()._80);
}

void StateSwing::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::bomb
