#ifndef SCN_STEP_ENEMY_ACCESSOR_H
#define SCN_STEP_ENEMY_ACCESSOR_H

#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

// TODO: the other functions, and whether the handle is a member or a base.
class Accessor {
public:
    Accessor();
    Accessor(Enemy* enemy);

    bool isValid() const;
    Enemy& obj();

private:
    util::ObjRefHandle<Enemy> mHandle;
};

}
}
}

#endif
