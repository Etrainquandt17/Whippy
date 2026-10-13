#ifndef SCN_STEP_HERO_ITEMCATCHER_H
#define SCN_STEP_HERO_ITEMCATCHER_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class ItemCatcher {
public:
    void setSize(const hel::math::Vector2& size, f32);
    void resetSize();
};

}}}  // namespace scn::step::hero

#endif
