#ifndef SCN_STEP_BOSS_GRANDLOWPER_COVERCTRL_H
#define SCN_STEP_BOSS_GRANDLOWPER_COVERCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace grandlowper {

// TODO: members.
class CoverCtrl {
public:
    void init();
    int getCoverHp() const;
    bool isCoverHpMax() const;
    bool isFirstChange() const;
};

}
}
}
}

#endif
