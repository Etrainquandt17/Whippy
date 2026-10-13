#ifndef SCN_STEP_ENEMY_LUPA_CLIFFCHECKER_H
#define SCN_STEP_ENEMY_LUPA_CLIFFCHECKER_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lupa {

class CliffChecker {
public:
    CliffChecker(Enemy& enemy);
    ~CliffChecker();

    void changeDirType(bool isUp);
    void setAccelDirRight(bool isRight);
    void update();
    bool isCliff() const;

private:
    Enemy& mObj;
    bool mIsCliff;
    f32 mDirV;
    f32 mAccelDir;
};

}
}
}
}

#endif
