#ifndef SCN_STEP_ENEMY_PLUID_BRAINJUMP_H
#define SCN_STEP_ENEMY_PLUID_BRAINJUMP_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

class BrainJump : public BrainBase {
public:
    BrainJump(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
