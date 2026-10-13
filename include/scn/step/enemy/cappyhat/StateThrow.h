#ifndef SCN_STEP_ENEMY_CAPPYHAT_STATETHROW_H
#define SCN_STEP_ENEMY_CAPPYHAT_STATETHROW_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappyhat {

class StateThrow : public StateBase {
public:
    StateThrow(Enemy* enemy, u64 ownerUid);
    virtual ~StateThrow();
    virtual void procMove();
    virtual void procFixPos();

private:
    u64 mOwnerUid;
};

}
}
}
}

#endif
