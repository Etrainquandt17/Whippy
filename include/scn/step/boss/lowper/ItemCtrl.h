#ifndef SCN_STEP_BOSS_LOWPER_ITEMCTRL_H
#define SCN_STEP_BOSS_LOWPER_ITEMCTRL_H

#include "gobj/GearAnim.h"
#include "gobj/GearModel.h"
#include "hel/math/Vector3.h"
#include "scn/step/item/Item.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

}
class Boss;
namespace lowper {

class ItemCtrl {
public:
    ItemCtrl(Boss& boss);
    ~ItemCtrl();

    void init();
    void update();
    bool isItemExist() const;
    void checkItemGather();
    bool isNearObj(hel::math::Vector3, hel::math::Vector3) const;
    hel::math::Vector3 getItemPos() const;
    void setupGear();
    void setupSRTTarget();

private:
    Boss& mBoss;
    util::ObjRefHandle<item::Item> mItem;
    util::ObjRefHandle<item::Item> mItemPair;
    gobj::GearModelDesc mGearModelDesc;
    gobj::GearAnimDesc mGearAnimDesc;
    f32 mRot;
    f32 mRotSpeed;
    f32 mScale;
    f32 mScaleTarget;
    bool mIsGathered;
    bool mIsInit;
    bool mIsEnd;
};

}}}}  // namespace scn::step::boss::lowper

#endif
