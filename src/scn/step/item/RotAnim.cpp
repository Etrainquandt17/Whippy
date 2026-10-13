#include "scn/step/item/RotAnim.h"

#include "scn/step/Component.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/Manager.h"

namespace scn {
namespace step {
namespace item {

RotAnim::RotAnim(Item& item)
    : mObj(item)
    , mSpeedKind(SPEED_KIND_SLOW) {
    f32 x = item.location().pos().x;
    mRot = item.comp().itemManager().getRotGlobal(x);
    mIsEnable = true;
}

// TODO: the original tests mIsEnable with `bne` over a `b` to the end where this has one `beq`; the rest matches.
void RotAnim::update() {
    if (!mObj.isRequireRotAnim()) {
        return;
    }
    if (mIsEnable) {
        mRot += currentSpeed();
        while (mRot < 0.0f) {
            mRot += 360.0f;
        }
        while (360.0f <= mRot) {
            mRot -= 360.0f;
        }
        mObj.model().rotCtrl().initRotH(mRot);
    } else {
        return;
    }
}

void RotAnim::setSpeed(SpeedKind kind) {
    mSpeedKind = kind;
}

bool RotAnim::isEnable() const {
    return mIsEnable;
}

void RotAnim::setIsEnable(bool isEnable) {
    mIsEnable = isEnable;
}

f32 RotAnim::currentSpeed() const {
    switch (mSpeedKind) {
    case SPEED_KIND_SLOW:
        return -4.0f;
    case SPEED_KIND_MIDDLE:
        return -6.0f;
    case SPEED_KIND_FAST:
        return -18.0f;
    default:
        return 0.0f;
    }
}

}}}  // namespace scn::step::item
