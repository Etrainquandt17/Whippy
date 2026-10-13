#ifndef SCN_STEP_ENEMY_COMMON_STATESUPERAPPEARPRE_H
#define SCN_STEP_ENEMY_COMMON_STATESUPERAPPEARPRE_H

#include "scn/step/enemy/StateBase.h"
#include "scn/step/ostop/Requestor.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateSuperAppearPre : public StateBase {
public:
    StateSuperAppearPre(Enemy* enemy, int _14);
    virtual ~StateSuperAppearPre();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    ostop::Requestor mRequestor;
    int _14;
};

}
}
}
}

#endif
