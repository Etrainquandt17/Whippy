#ifndef SCN_STEP_ENEMY_OWGULF_BRAINFLYAROUND_H
#define SCN_STEP_ENEMY_OWGULF_BRAINFLYAROUND_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

class BrainFlyAround : public BrainBase {
public:
    BrainFlyAround(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual void update();

private:
    f32 mBaseX;
};

}
}
}
}

#endif
