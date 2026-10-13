#ifndef SCN_STEP_ENEMY_PARASOLDOO_BRAINNOSEDIVE_H
#define SCN_STEP_ENEMY_PARASOLDOO_BRAINNOSEDIVE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasoldoo {

class BrainNoseDive : public BrainBase {
public:
    BrainNoseDive(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual void update();
};

}
}
}
}

#endif
