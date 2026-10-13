#ifndef SCN_STEP_CHARA_HITPOINT_H
#define SCN_STEP_CHARA_HITPOINT_H

#include "types.h"

namespace scn {
namespace step {
namespace chara {

// TODO: members.
class HitPoint {
public:
    HitPoint();

    void init(u32 value);
    void initDeadBent(u32 value);
    void set(u32 value);
    void setMin(u32 value);
    void resetMin();
    void inc(u32 value);
    void dec(u32 value);
    void decDeadBent(u32 value);
    u32 get() const;
    u32 getMax() const;
    u32 getPrev() const;
    f32 rate() const;
    bool isFull() const;
    bool isDead() const;
    bool isDeadPrev() const;
    bool isDeadBentZero() const;
};

}
}
}

#endif
