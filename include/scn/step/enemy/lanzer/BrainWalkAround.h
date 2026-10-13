#ifndef SCN_STEP_ENEMY_LANZER_BRAINWALKAROUND_H
#define SCN_STEP_ENEMY_LANZER_BRAINWALKAROUND_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

class BrainWalkAround : public BrainBase {
public:
    BrainWalkAround(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual bool onLanding();
};

}
}
}
}

#endif
