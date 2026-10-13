#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAIN6WAYSHOTNOPREP_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAIN6WAYSHOTNOPREP_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

class Brain6WayShotNoPrep : public BrainBase {
public:
    Brain6WayShotNoPrep(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
