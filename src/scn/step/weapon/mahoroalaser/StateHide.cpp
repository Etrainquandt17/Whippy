#include "scn/step/weapon/mahoroalaser/StateHide.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroalaser/Custom.h"
#include "scn/step/weapon/mahoroalaser/StateMain.h"
#include "scn/step/weapon/mahoroalaser/StateReady.h"

using hel::common::DynamicCast;

namespace scn {
namespace step {
namespace weapon {
namespace mahoroalaser {

StateHide::StateHide(Weapon* weapon) : StateBase(weapon) {
    obj().model().setVisibility(false);
}

StateHide::~StateHide() {
    obj().model().setVisibility(true);
}

void StateHide::procAnim() {
    Custom* custom = DynamicCast<Custom*, ICustom>(obj().custom());
    if (custom->isStartRequested()) {
        if (custom->getReadyFrame() == 0) {
            obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
        } else {
            obj().stateChanger().setNextState<StateReady, Weapon*>(&obj());
        }
    }
}

void StateHide::procMove() {}

void StateHide::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroalaser
