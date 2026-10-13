#ifndef SCN_STEP_HERO_INERTIALMOVE_H
#define SCN_STEP_HERO_INERTIALMOVE_H

#include "hel/math/Vector3.h"

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class InertialMove {
public:
    void setVelocity(const hel::math::Vector3& velocity);
};

}}}  // namespace scn::step::hero

#endif
