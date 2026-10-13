#ifndef SCN_SUBGAME_GUNSHOOT_ENEMY_COLLISIONITEM_H
#define SCN_SUBGAME_GUNSHOOT_ENEMY_COLLISIONITEM_H

#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace enemy {

class CollisionItem {
public:
    bool isActive() const;
    void deactivate();
    int shieldValue() const;
    void addDamage(int damage);
    bool isBroken() const;
    void recover();

private:
    u8 _0[0xF8];
    bool _F8;
    bool _F9;
    int mShieldValue;
    int _100;
    int _104;
};

}
}
}
}

#endif
