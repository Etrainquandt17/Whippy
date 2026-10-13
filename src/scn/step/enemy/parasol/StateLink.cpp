#include "scn/step/enemy/parasol/StateLink.h"

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
#include "scn/step/enemy/parasol/Custom.h"
#include "scn/step/enemy/parasol/StateRise.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasol {

StateLink::StateLink(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().mapColl().setValid(false);
    obj().nururi().setCanNururi(false);
    obj().nururi().setValid(false);
    obj().model().rotCtrl().initRotH(0.0f);
    obj().model().rotCtrl().setValid(false);
}

void StateLink::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isStateChange() == true) {
        obj().stateChanger().setNextState<StateRise, Enemy*>(objPtr());
        custom.offStateChange();
    }
}

}}}}  // namespace scn::step::enemy::parasol
