#ifndef SCN_STEP_ENEMY_SHOTZO_BRAINFIXCEIL_H
#define SCN_STEP_ENEMY_SHOTZO_BRAINFIXCEIL_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

class BrainFixCeil : public BrainBase {
public:
    BrainFixCeil(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
