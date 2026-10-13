#ifndef SCN_STEP_HERO_SQUASH_H
#define SCN_STEP_HERO_SQUASH_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Squash {
public:
    hel::math::Vector3 getCurrentScale() const;
    void setTarget(const hel::math::Vector3& scale, f32 rate);
};

}}}  // namespace scn::step::hero

#endif
