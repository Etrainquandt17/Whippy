#ifndef SCN_STEP_ENEMY_CAPPY_STATELOSTHAT_H
#define SCN_STEP_ENEMY_CAPPY_STATELOSTHAT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappy {

class StateLostHat : public StateBase {
public:
    StateLostHat(Enemy* enemy);
    virtual ~StateLostHat();
    virtual void procAnim();
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
