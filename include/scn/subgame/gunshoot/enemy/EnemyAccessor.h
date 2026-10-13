#ifndef SCN_SUBGAME_GUNSHOOT_ENEMY_ENEMYACCESSOR_H
#define SCN_SUBGAME_GUNSHOOT_ENEMY_ENEMYACCESSOR_H

#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace enemy {

class EnemyAccessor {
public:
    ~EnemyAccessor();

    bool isDead() const;
    bool isClimax() const;
    bool isExtraClimax() const;
    bool isClimaxAndAfter() const;

private:
    u32 _0;
};

}
}
}
}

#endif
