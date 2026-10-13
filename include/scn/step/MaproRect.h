#ifndef SCN_STEP_MAPRORECT_H
#define SCN_STEP_MAPRORECT_H

#include "hel/geo/Rect.h"
#include "types.h"

namespace scn {
namespace step {

class MaproRect {
public:
    MaproRect(s32 x, s32 y, u32 width, u32 height);

    hel::geo::Rect toWorldRect() const;

private:
    // TODO: the layout is a guess from the constructor's arguments.
    s32 mX;
    s32 mY;
    u32 mWidth;
    u32 mHeight;
};

}}  // namespace scn::step

#endif
