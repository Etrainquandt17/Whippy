#ifndef SCN_STEP_CHARA_CULLING_H
#define SCN_STEP_CHARA_CULLING_H

#include "types.h"

namespace hel {
namespace geo {

class Rect;

}}  // namespace hel::geo

namespace scn {
namespace step {
namespace chara {

// TODO: members and the other functions.
class Culling {
public:
    void setValid(bool isValid);
    void setHeight(f32 height);
    hel::geo::Rect calcCullingRect() const;
};

}}}  // namespace scn::step::chara

#endif
