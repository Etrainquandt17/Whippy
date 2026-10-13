#ifndef SCN_STEP_BOSS_COMMON_DEADUTIL_H
#define SCN_STEP_BOSS_COMMON_DEADUTIL_H

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace common {

class DeadUtil {
public:
    static void RequestDeadEffect(Boss& boss, bool isWeak);
};

}
}
}
}

#endif
