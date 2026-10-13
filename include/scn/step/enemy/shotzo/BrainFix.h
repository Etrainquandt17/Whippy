#ifndef SCN_STEP_ENEMY_SHOTZO_BRAINFIX_H
#define SCN_STEP_ENEMY_SHOTZO_BRAINFIX_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

class BrainFix : public BrainBase {
public:
    BrainFix(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
