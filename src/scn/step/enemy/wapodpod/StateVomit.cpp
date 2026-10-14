#include "scn/step/enemy/wapodpod/StateVomit.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/wapodpod/Custom.h"
#include "scn/step/enemy/wapodpod/StateWait.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace wapodpod {

StateVomit::StateVomit(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(7);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).requestWapod();
    obj().effect().state().requestN(static_cast<effect::Kind>(0x557), 1);
    obj().soundSEState().start(0x303);
}

void StateVomit::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    }
}

void StateVomit::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::wapodpod
