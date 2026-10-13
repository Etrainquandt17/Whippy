#ifndef OCOLL_SEARCHHIT_H
#define OCOLL_SEARCHHIT_H

#include "types.h"

namespace ocoll {

// TODO: members and the other functions.
class SearchHit {
public:
    bool isCollide() const;
    u32 getCollidedNum() const;
    u64 getCollidedHitOwnerUid(u32 index) const;
    u64 getCollidedHitOwnerRootUid(u32 index) const;
};

}

#endif
