#include "scn/step/enemy/shotzo/StateAim.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/shotzo/Custom.h"
#include "scn/step/enemy/shotzo/ParamData.h"
#include "snd/SERequestor.h"

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
