#ifndef SCN_STEP_ENEMY_BABUT_STATEHANG_H
#define SCN_STEP_ENEMY_BABUT_STATEHANG_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace babut {

class StateHang : public StateBase {
public:
    StateHang(Enemy* enemy);
    virtual void procMove();
};

}
}
}
}

#endif
