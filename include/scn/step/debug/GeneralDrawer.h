#ifndef SCN_STEP_DEBUG_GENERALDRAWER_H
#define SCN_STEP_DEBUG_GENERALDRAWER_H

#include "hel/math/Vector2.h"
#include "revolution/gx/GXStruct.h"

namespace scn {
namespace step {
namespace debug {

// TODO: members and the other functions.
class GeneralDrawer {
public:
    void addArrow(const hel::math::Vector2& from, const hel::math::Vector2& to);
    void addPoint(const hel::math::Vector2& pos);
    void addPoint(const hel::math::Vector2& pos, const GXColor& color);
};

}}}  // namespace scn::step::debug

#endif
