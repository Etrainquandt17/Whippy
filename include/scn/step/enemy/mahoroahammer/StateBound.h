#ifndef SCN_STEP_ENEMY_MAHOROAHAMMER_STATEBOUND_H
#define SCN_STEP_ENEMY_MAHOROAHAMMER_STATEBOUND_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroahammer {

class StateBound : public StateBase {
public:
    StateBound(Enemy* enemy, const hel::math::Vector2& velocity);
    virtual ~StateBound();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
