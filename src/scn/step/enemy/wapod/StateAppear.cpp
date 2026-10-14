#include "scn/step/enemy/wapod/StateAppear.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/wapod/Custom.h"
#include "scn/step/enemy/wapod/StateRise.h"
#include "scn/step/enemy/wapod/StateStay.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

StateAppear::StateAppear(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(7);
}

StateAppear::~StateAppear() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).fixPosInValid();
}

void StateAppear::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().isAllEnd()) {
        custom.fixPosInValid();
        obj().nururi().setValid(true);
        u32 variation = custom.wapodpodVariation();
        if (variation == 0xad) {
            obj().stateChanger().setNextState<StateRise, Enemy*>(objPtr());
        } else if (variation == 0xae) {
            obj().stateChanger().setNextState<StateStay, Enemy*>(objPtr());
        }
    }
}

void StateAppear::procMove() {}

void StateAppear::procFixPos() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).landHitDead();
}

}}}}  // namespace scn::step::enemy::wapod
