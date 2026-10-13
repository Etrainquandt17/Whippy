#ifndef SCN_STEP_CARRYITEM_BOUNDALGORITHM_H
#define SCN_STEP_CARRYITEM_BOUNDALGORITHM_H

#include "types.h"

namespace scn {
namespace step {
namespace carryitem {

class CarryItem;

class BoundAlgorithm {
public:
    BoundAlgorithm(CarryItem& carryItem, u32 boundSE);
    BoundAlgorithm(CarryItem& carryItem);
    ~BoundAlgorithm();

    void init();
    void procMove();
    void procFixPos();
    u32 getCount();
    void setSpeedV(f32 speed);
    void setReduceV(f32 reduce);
    void setRateH(f32 rate);
    void setRateVRoof(f32 rate);
    bool isBound();
    void setIsBound(bool isBound);

private:
    CarryItem& obj() { return mObj; }

    CarryItem& mObj;
    u32 mCount;
    bool mIsBound;
    u32 mFloorSEInterval;
    u32 mWallSEInterval;
    u32 mRoofSEInterval;
    u32 mCageSEInterval;
    f32 mSpeedV;
    f32 mReduceV;
    f32 mRateH;
    f32 mRateVRoof;
    u32 mBoundSE;
};

}}}  // namespace scn::step::carryitem

#endif
