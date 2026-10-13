#ifndef SCN_STEP_ENEMY_METALGENERALBIT_BRAINMAIN_H
#define SCN_STEP_ENEMY_METALGENERALBIT_BRAINMAIN_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

class BrainMain : public BrainBase {
public:
    BrainMain(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
