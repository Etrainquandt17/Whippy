#include "scn/step/hero/common/StateEat.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/gimmick/Manager.h"
#include "scn/step/hero/AdditionalMove.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateDrink.h"
#include "scn/step/hero/common/StateJumpStart.h"
#include "scn/step/hero/common/StateRun.h"
#include "scn/step/hero/common/StateVomit.h"
#include "scn/step/hero/common/StateWalk.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateEat::StateEat(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().model().script().start(0x15);
    if (obj().isMainPlayer()) {
        obj().comp().gimmickManager().onEat(obj().location().pos());
    }
    obj().additionalMove().setForbidChangeState(true);
}

StateEat::~StateEat() {}

void StateEat::procAnim() {
    mFrame++;
    if (StateDrink::TryToChangeState(objPtr()) || StateVomit::TryToChangeState(objPtr()) ||
        StateJumpStart::TryToChangeState(objPtr()) || StateRun::TryToChangeState(objPtr())) {
        return;
    }
    if (mFrame >= 11 && StateWalk::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateEat::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateEat::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::common
