#ifndef SCN_STEP_HERO_WEAPONCTRL_H
#define SCN_STEP_HERO_WEAPONCTRL_H

#include "hel/math/Vector2.h"

namespace scn {
namespace step {
namespace hero {

// TODO: members and the other functions.
class WeaponCtrl {
public:
    void setup();
    void update();
    void reserveStarFront();
    void requestBurstMain();
    void requestBurstSub(hel::math::Vector2 dir);
    void requestCannon();
    void requestStarBack(hel::math::Vector2 dir);
};

}}}  // namespace scn::step::hero

#endif
