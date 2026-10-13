#ifndef SCN_STEP_ENEMY_ALGORITHM_ALGORITHMMAHOROA1DISAPPEAR_H
#define SCN_STEP_ENEMY_ALGORITHM_ALGORITHMMAHOROA1DISAPPEAR_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace algorithm {

class AlgorithmMahoroa1Disappear {
public:
    AlgorithmMahoroa1Disappear(Enemy& enemy);
    ~AlgorithmMahoroa1Disappear();

    void procAnim();
    void procMove();
    bool isEnd() const;

private:
    Enemy& mObj;
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::algorithm

#endif
