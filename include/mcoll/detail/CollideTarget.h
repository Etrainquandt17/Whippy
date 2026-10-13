#ifndef MCOLL_DETAIL_COLLIDETARGET_H
#define MCOLL_DETAIL_COLLIDETARGET_H

#include "hel/geo2d/Edge.h"
#include "types.h"

namespace mcoll {
namespace detail {

// TODO: the bytes at 1 to 6 (the land's property, attribute and through type among them) and the other functions.
class CollideTarget {
public:
    bool isValid() const;
    void setIsEnableDetect(bool isEnable);
    hel::geo2d::Edge edge() const { return mEdge; }

    bool mIsValid;
    u8 _1[4];
    s8 _5;
    u8 _6[2];
    hel::geo2d::Edge mEdge;
};

}
}

#endif
