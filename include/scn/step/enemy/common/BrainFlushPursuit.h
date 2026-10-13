#ifndef SCN_STEP_ENEMY_COMMON_BRAINFLUSHPURSUIT_H
#define SCN_STEP_ENEMY_COMMON_BRAINFLUSHPURSUIT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class BrainFlushPursuit : public BrainBase {
public:
    BrainFlushPursuit(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
