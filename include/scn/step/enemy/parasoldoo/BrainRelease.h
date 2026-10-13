#ifndef SCN_STEP_ENEMY_PARASOLDOO_BRAINRELEASE_H
#define SCN_STEP_ENEMY_PARASOLDOO_BRAINRELEASE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasoldoo {

class BrainRelease : public BrainBase {
public:
    BrainRelease(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual void update();
};

}
}
}
}

#endif
