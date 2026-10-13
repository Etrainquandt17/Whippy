#ifndef SCN_STEP_ENEMY_SHOTZO_BRAINPURSUIT_H
#define SCN_STEP_ENEMY_SHOTZO_BRAINPURSUIT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

class BrainPursuit : public BrainBase {
public:
    BrainPursuit(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
