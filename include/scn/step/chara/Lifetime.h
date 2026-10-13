#ifndef SCN_STEP_CHARA_LIFETIME_H
#define SCN_STEP_CHARA_LIFETIME_H

#include "types.h"

namespace scn {
namespace step {
namespace chara {

class Lifetime {
public:
    Lifetime();

    void update();
    void set(u32 frame);
    u32 get() const;
    bool isDead() const;
    void setAgeless();
    void unsetAgeless();

private:
    bool mIsAgeless;
    u32 mFrame;
};

}
}
}

#endif
