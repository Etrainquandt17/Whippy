#ifndef SCN_STEP_HERO_NODEATTACH_H
#define SCN_STEP_HERO_NODEATTACH_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: members and the other functions.
class NodeAttach {
public:
    void setOffset(const hel::math::Vector3& offset);
    void setRotate(const hel::math::Vector3& rotate);
    void setScale(f32 scale);
};

}}}  // namespace scn::step::hero

#endif
