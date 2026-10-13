#ifndef UTIL_SINTAABBOX_H
#define UTIL_SINTAABBOX_H

#include "types.h"

namespace util {

class SIntAABBox {
public:
    SIntAABBox(s32 x, s32 y, u32 width, u32 height);

    // TODO: name. Seen expanded in scn::step::gimmick::block::Block::isExistBlock.
    bool isInclude(s32 x, s32 y) const { return mMinX <= x && x < mMaxX && mMinY <= y && y < mMaxY; }

    s32 mMinX;
    s32 mMinY;
    s32 mMaxX;
    s32 mMaxY;
};

}  // namespace util

#endif
