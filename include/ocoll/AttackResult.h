#ifndef OCOLL_ATTACKRESULT_H
#define OCOLL_ATTACKRESULT_H

#include "types.h"

namespace ocoll {

// TODO: the other members, and the size.
struct AttackResultData {
    u32 _0[0x10 / 4];
    u64 mOwnerID;
};

// TODO: members and the other functions.
class AttackResult {
public:
    const AttackResultData& getData(u32 index) const;
    bool isCollide() const;
    u32 dataNum() const;
};

}

#endif
