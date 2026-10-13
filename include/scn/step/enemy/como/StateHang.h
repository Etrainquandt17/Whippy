#ifndef SCN_STEP_ENEMY_COMO_STATEHANG_H
#define SCN_STEP_ENEMY_COMO_STATEHANG_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

class StateHang : public StateBase {
public:
    StateHang(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();
};

}
}
}
}

#endif
