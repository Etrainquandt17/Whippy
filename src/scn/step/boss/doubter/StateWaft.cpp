#include "scn/step/boss/doubter/StateWaft.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateWaft::StateWaft(Boss* boss) : StateBase(boss), _8(0.0f) {
    obj().footState().setAir();
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    obj().model().reqScript(0);
    obj().brainCtrl().toValid();
    obj().move().resetVelocity();
}

StateWaft::~StateWaft() {}

void StateWaft::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateWaft::procMove() {
    obj().location().setPos(DynamicCastToRef<Custom, ICustom>(obj().custom()).waftPositionCtrl().getNextPos());
}

void StateWaft::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
