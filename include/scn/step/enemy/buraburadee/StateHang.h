#ifndef SCN_STEP_ENEMY_BURABURADEE_STATEHANG_H
#define SCN_STEP_ENEMY_BURABURADEE_STATEHANG_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace buraburadee {

class StateHang : public StateBase {
public:
    StateHang(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
