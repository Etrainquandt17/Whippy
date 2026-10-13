#ifndef SCN_STEP_ENEMY_ALGORITHM_ALGORITHMGRANDLOWPERAPPEAR_H
#define SCN_STEP_ENEMY_ALGORITHM_ALGORITHMGRANDLOWPERAPPEAR_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace algorithm {

class AlgorithmGrandLowperAppear {
public:
    AlgorithmGrandLowperAppear(Enemy& enemy);
    ~AlgorithmGrandLowperAppear();

    void procAnim();
    void procMove();
    void updateHoldFrameRate();
    f32 getHoldFrameRate() const;
    bool isHoldEnd() const;

private:
    Enemy& mObj;
    s32 mHoldFrame;
    f32 mHoldFrameRate;
    f32 _c;
};

}}}}  // namespace scn::step::enemy::algorithm

#endif
