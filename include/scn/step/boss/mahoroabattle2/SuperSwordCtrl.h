#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_SUPERSWORDCTRL_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_SUPERSWORDCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle2 {

// TODO: members.
class SuperSwordCtrl {
public:
    struct ReqData {
        u32 _0;
    };

    void addReqData(const ReqData& data);
    void clearReqData();
};

}
}
}
}

#endif
