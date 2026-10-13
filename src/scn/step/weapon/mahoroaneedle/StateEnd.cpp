#include "scn/step/weapon/mahoroaneedle/StateEnd.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroaneedle/Custom.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

StateEnd::StateEnd(Weapon* weapon) : StateBase(weapon) {
    obj().model().rotCtrl().setValid(false);
    obj().model().reqScript(3);
    obj().effect().normal().requestN(
        static_cast<effect::Kind>(obj().kind() == 0x4E ? 0x42B : (Utility::IsExtra(obj()) ? 0x3D3 : 0x3E9)), 0
    );
}

StateEnd::~StateEnd() {}

void StateEnd::procAnim() {
    hel::common::DynamicCast<Custom*, ICustom>(obj().custom())->updateRot(10.0f);
    if (obj().model().isAllEnd()) {
        obj().dead();
    }
}

void StateEnd::procMove() {}

void StateEnd::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroaneedle
