#include "scn/step/enemy/parasol/StateLink.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/parasol/Custom.h"
#include "scn/step/enemy/parasol/StateRise.h"

using hel::common::DynamicCastToRef;

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
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isStateChange() == true) {
        obj().stateChanger().setNextState<StateRise, Enemy*>(objPtr());
        custom.offStateChange();
    }
}

}}}}  // namespace scn::step::enemy::parasol
