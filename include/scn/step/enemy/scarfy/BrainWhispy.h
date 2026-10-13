#ifndef SCN_STEP_ENEMY_SCARFY_BRAINWHISPY_H
#define SCN_STEP_ENEMY_SCARFY_BRAINWHISPY_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

class BrainWhispy : public BrainBase {
public:
    BrainWhispy(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
