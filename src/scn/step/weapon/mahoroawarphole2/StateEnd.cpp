#include "scn/step/weapon/mahoroawarphole2/StateEnd.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroawarphole2/Custom.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarphole2 {

StateEnd::StateEnd(Weapon* weapon) : StateBase(weapon) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().culling().setValid(false);
    obj().model().rotCtrl().setValid(false);
    obj().mapColl().setValid(false);
    obj().model().reqScript(2);
}

StateEnd::~StateEnd() {
    obj().effect().normal().release();
    obj().effect().warp().release();
}

void StateEnd::procAnim() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).updateFlash();
    if (obj().model().isAllEnd()) {
        obj().dead();
    }
}

void StateEnd::procMove() {}

void StateEnd::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroawarphole2
