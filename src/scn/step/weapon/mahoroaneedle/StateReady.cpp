#include "scn/step/weapon/mahoroaneedle/StateReady.h"

#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

StateReady::StateReady(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    obj().model().rotCtrl().setValid(false);
    obj().model().reqScript(0);
    obj().effect().normal().requestN(
        static_cast<effect::Kind>(obj().kind() == 0x4E ? 0x429 : (Utility::IsExtra(obj()) ? 0x3D1 : 0x3E7)), 0
    );
    obj().effect().normal().requestN(
        static_cast<effect::Kind>(obj().kind() == 0x4E ? 0x428 : (Utility::IsExtra(obj()) ? 0x3D0 : 0x3E6)), 0
    );
}

StateReady::~StateReady() {
    obj().effect().normal().release();
}

void StateReady::procAnim() {
    if (++mFrame == 50) {
        obj().effect().normal().release();
        obj().effect().normal().requestN(
            static_cast<effect::Kind>(obj().kind() == 0x4E ? 0x427 : (Utility::IsExtra(obj()) ? 0x3CF : 0x3E5)), 0
        );
    }
}

void StateReady::procMove() {}

void StateReady::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroaneedle
