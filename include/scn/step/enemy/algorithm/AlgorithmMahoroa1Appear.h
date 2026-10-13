#ifndef SCN_STEP_ENEMY_ALGORITHM_ALGORITHMMAHOROA1APPEAR_H
#define SCN_STEP_ENEMY_ALGORITHM_ALGORITHMMAHOROA1APPEAR_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace algorithm {

class AlgorithmMahoroa1Appear {
public:
    AlgorithmMahoroa1Appear(Enemy& enemy);
    ~AlgorithmMahoroa1Appear();

    void procAnim();
    void procMove();
    bool isEnd() const;

private:
    Enemy& mObj;
    u32 mFrame;
};

}
}
}
}

#endif
