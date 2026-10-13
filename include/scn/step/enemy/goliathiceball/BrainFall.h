#ifndef SCN_STEP_ENEMY_GOLIATHICEBALL_BRAINFALL_H
#define SCN_STEP_ENEMY_GOLIATHICEBALL_BRAINFALL_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathiceball {

class BrainFall : public BrainBase {
public:
    BrainFall(Enemy& enemy);
    virtual bool onStart();
    virtual bool onLanding();
};

}
}
}
}

#endif
