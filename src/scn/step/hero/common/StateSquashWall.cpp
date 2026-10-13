#include "scn/step/hero/common/StateSquashWall.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/AdditionalMove.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Nururi.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateDrink.h"
#include "scn/step/hero/common/StateJumpStart.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StateSliding.h"
#include "scn/step/hero/common/StateSquat.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateVomit.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "scn/step/map/LandManager.h"
#include "scn/step/map/MoveGroupAccessor.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateSquashWall::TryToChangeState(Hero* hero) {
    if (hero->stateChecker().isBombDanger()) {
        return false;
    }
    f32 nururi = hero->nururi().getNururiDir().x;
    if (!hel::math::Math::EqZero(nururi)) {
        f32 sign = hero->target().getSign();
        if (sign * nururi < 0.0f) {
            return false;
        }
    }
    if (hero->target().isRightDir() && hero->mapColl().is_8E()) {
        return false;
    }
    if (!hero->target().isRightDir() && hero->mapColl().is_8F()) {
        return false;
    }
    bool isFlowRight = false;
    bool isFlowLeft = false;
    hel::math::Vector2 airFlow = hero->additionalMove().airFlowVector();
    if (!hel::math::Math::EqZero(airFlow.x)) {
        bool isPlus = airFlow.x > 0.0f;
        if (isPlus) {
            isFlowRight = true;
        }
        if (!isPlus) {
            isFlowLeft = true;
        }
    }
    if (hero->target().isRightDir() && isFlowLeft) {
        return false;
    }
    if (!hero->target().isRightDir() && isFlowRight) {
        return false;
    }
    MapCollResult result = hero->mapColl().result();
    f32 sign = hero->target().getSign();
    hel::math::Vector2 delta = hel::math::Vector2::ZERO;
    if (mcoll::detail::MoveGridGroupId(result._20).isValid()) {
        delta += hero->comp().mapLandManager().mgAccessor().deltaSafe(mcoll::detail::MoveGridGroupId(result._20));
    }
    if (mcoll::detail::MoveGridGroupId(result._1c).isValid()) {
        delta -= hero->comp().mapLandManager().mgAccessor().deltaSafe(mcoll::detail::MoveGridGroupId(result._1c));
    }
    if (sign * delta.x > 0.0f) {
        return false;
    }
    if (result._2) {
        hero->stateChanger().setNextState<StateSquashWall, Hero*>(hero);
        return true;
    }
    return false;
}

StateSquashWall::StateSquashWall(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().model().script().start(0x3C);
    obj().move().setSpeedH(0.002f * obj().target().getSign());
}

StateSquashWall::~StateSquashWall() {
}

void StateSquashWall::procAnim() {
    mFrame++;
    obj().abilityManager().chkDiscardAbility();
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) || StateCarryItemPut::TryToChangeState(objPtr()) ||
        StateCarryItemThrow::TryToChangeState(objPtr()) || obj().abilityManager().tryToChangeState() ||
        StateDrink::TryToChangeState(objPtr()) || StateSliding::TryToChangeState(objPtr()) ||
        StateVomit::TryToChangeState(objPtr()) || StateVacuum::TryToChangeState(objPtr()) ||
        StateSquat::TryToChangeState(objPtr()) || StateLadder::TryToChangeState(objPtr()) ||
        StateJumpStart::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSquashWall::procMove() {
    if (mFrame < 5) {
        obj().move().decel(gobj::MoveParamDecel::Zero());
    } else {
        Utility::MoveDefault(obj());
    }
}

void StateSquashWall::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
