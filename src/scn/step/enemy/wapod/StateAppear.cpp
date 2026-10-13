#include "scn/step/enemy/wapod/StateAppear.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/wapod/Custom.h"
#include "scn/step/enemy/wapod/StateRise.h"
#include "scn/step/enemy/wapod/StateStay.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

StateAppear::StateAppear(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(7);
}

StateAppear::~StateAppear() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).fixPosInValid();
}

void StateAppear::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
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
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).landHitDead();
}

}}}}  // namespace scn::step::enemy::wapod
