#ifndef SCN_STEP_ENEMY_CAPPY_STATESKINNED_H
#define SCN_STEP_ENEMY_CAPPY_STATESKINNED_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappy {

class StateSkinned : public StateBase {
public:
    StateSkinned(Enemy* enemy);
    virtual ~StateSkinned();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}
}
}
}

#endif
