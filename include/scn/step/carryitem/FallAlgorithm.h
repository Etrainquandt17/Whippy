#ifndef SCN_STEP_CARRYITEM_FALLALGORITHM_H
#define SCN_STEP_CARRYITEM_FALLALGORITHM_H

#include "types.h"

namespace scn {
namespace step {
namespace carryitem {

class CarryItem;

class FallAlgorithm {
public:
    FallAlgorithm(CarryItem& carryItem);
    FallAlgorithm(CarryItem& carryItem, u32 boundSE);
    ~FallAlgorithm();

    void init();
    void procAnim();
    void procMove();
    void procFixPos();
    void procObjCollReact();
    void setRotH(f32 rotH);
    void setRotSpeedRate(f32 rate);
    void setIsBounded(bool isBounded);
    bool isBreakEnemy(u64 uid);
    bool isCollideBossOrEnemy();
    void setAttack();

private:
    CarryItem& obj() { return mObj; }

    CarryItem& mObj;
    bool mIsBounded;
    bool mIsRotMinus;
    f32 mRotV;
    f32 mRotH;
    f32 mRotSpeedRate;
    u32 mBoundSE;
};

}}}  // namespace scn::step::carryitem

#endif
