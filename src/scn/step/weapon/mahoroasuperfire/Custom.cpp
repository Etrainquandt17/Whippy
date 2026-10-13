#include "scn/step/weapon/mahoroasuperfire/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroasuperfire/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroasuperfire {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mIsMoveLimitRectValid(false), mMoveLimitRect() {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::setMoveLimitRect(const hel::geo::Rect& rect) {
    // TODO: the original assigns the Rect, whose assignment hel/geo/Rect.h only declares.
    mMoveLimitRect._0 = rect._0;
    mMoveLimitRect._4 = rect._4;
    mMoveLimitRect._8 = rect._8;
    mMoveLimitRect._C = rect._C;
    mIsMoveLimitRectValid = true;
}

bool Custom::isMoveLimitRectValid() const {
    return mIsMoveLimitRectValid;
}

hel::geo::Rect Custom::getMoveLimitRect() const {
    return mMoveLimitRect;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::mahoroasuperfire
