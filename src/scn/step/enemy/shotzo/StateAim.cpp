#include "scn/step/enemy/shotzo/StateAim.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/shotzo/Custom.h"
#include "scn/step/enemy/shotzo/ParamData.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

StateAim::StateAim(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 angle = roundAngle(custom.aimAngle());
    mStartAngle = angle;
    mEndAngle = angle;
    mEndAngle += custom.playerAngle() > custom.aimAngle() ? 45.0f : -45.0f;
    mEndAngle = roundAngle(mEndAngle);
}

void StateAim::procAnim() {
    const ParamData& param = obj().param().shotzo();
    if (mFrame < param.mAimFrame) {
        mFrame++;
    } else {
        obj().brainCtrl().toValid();
    }
    f32 angle = mStartAngle + static_cast<f32>(mFrame) * (mEndAngle - mStartAngle) / static_cast<f32>(param.mAimFrame);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setAimAngle(angle);
}

void StateAim::procMove() {
    const common::ParamData& param = obj().param().common();
    if (!DynamicCastToRef<Custom, ICustom>(obj().custom()).isFixPos() && obj().footState().isAir()) {
        obj().move().airDecelFall(param.mDecel, param.mFall);
    } else {
        obj().move().resetSpeedV();
    }
}

void StateAim::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().footState().setGround();
    } else {
        obj().footState().setAir();
    }
}

f32 StateAim::roundAngle(f32 angle) {
    return nw4r::math::FFloor((angle + 22.5f) / 45.0f) * 45.0f;
}

}}}}  // namespace scn::step::enemy::shotzo
