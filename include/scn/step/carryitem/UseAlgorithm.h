#ifndef SCN_STEP_CARRYITEM_USEALGORITHM_H
#define SCN_STEP_CARRYITEM_USEALGORITHM_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {

class CarryItem;

class UseAlgorithm {
public:
    UseAlgorithm(CarryItem& carryItem);
    UseAlgorithm(CarryItem& carryItem, u32 useSE, u32 throwSE);
    ~UseAlgorithm();

    void init();
    void procAnim();
    void procMove();
    bool procConstraint();
    void setOffset(const hel::math::Vector3& offset);

private:
    CarryItem& obj() { return mObj; }

    CarryItem& mObj;
    bool mIsRightDir;
    bool mIsBackDir;
    f32 mRotH;
    hel::math::Vector3 mOffset;
    hel::math::Vector3 mOwnerPos;
    u32 mUseSE;
    u32 mThrowSE;
};

}}}  // namespace scn::step::carryitem

#endif
