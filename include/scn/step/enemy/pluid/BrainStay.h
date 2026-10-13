#ifndef SCN_STEP_ENEMY_PLUID_BRAINSTAY_H
#define SCN_STEP_ENEMY_PLUID_BRAINSTAY_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

class BrainStay : public BrainBase {
public:
    BrainStay(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
