#ifndef SCN_STEP_GRIDPOS_H
#define SCN_STEP_GRIDPOS_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {

class GridPos {
public:
    GridPos();
    GridPos(s32 x, s32 y);
    GridPos(const hel::math::Vector2& pos);

    hel::math::Vector2 toWorldPos() const;
    hel::math::Vector2 toWorldPosAtCenter() const;
    bool isPositivePos() const;
    s32 x() const { return mX; }
    s32 y() const { return mY; }

private:
    s32 mX;
    s32 mY;
};

}
}

#endif
