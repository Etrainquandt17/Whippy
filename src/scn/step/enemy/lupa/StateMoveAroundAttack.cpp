#include "scn/step/enemy/lupa/StateMoveAroundAttack.h"

#include "gobj/Anim.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/lupa/CliffChecker.h"
#include "scn/step/enemy/lupa/Custom.h"
#include "scn/step/enemy/lupa/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace lupa {

namespace {

// TODO: chara::MapCollResult::isHitWall(), which the shared header declares without its body.
inline bool t_IsHitWall(const chara::MapCollResult& result) {
    return result._2 || result._3;
}

}

StateMoveAroundAttack::StateMoveAroundAttack(Enemy* enemy)
    : StateBase(enemy), mWaitFrame(0), mAttackFrame(0), mIsRight(false), mRange(0.0f), mWaitLength(0) {
    const ParamData& param = obj().param().lupa();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(3);
    custom.cliffChecker().setAccelDirRight(mIsRight);
    mRange = obj().variation() == 0xf3 ? param.mMoveRangeFar : param.mMoveRange;
    switch (static_cast<u32>(obj().level())) {
    case 0:
        mWaitLength = param.mAttackWaitLv0;
        break;
    case 1:
        mWaitLength = param.mAttackWaitLv1;
        break;
    default:
        mWaitLength = param.mAttackWaitLv2;
        break;
    }
}

StateMoveAroundAttack::~StateMoveAroundAttack() {}

void StateMoveAroundAttack::procAnim() {
    const ParamData& param = obj().param().lupa();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::TurnHero(obj());
    if (obj().model().getCurrentScriptIndex() == 7) {
        mAttackFrame++;
        if (mAttackFrame == param.mWaitAttackShotFrame) {
            custom.reqShot();
        }
        if (obj().model().anim().isAnimEnd()) {
            obj().model().reqScript(3);
        }
    } else {
        mAttackFrame = 0;
        if (mWaitFrame < mWaitLength) {
            mWaitFrame++;
        } else if (!Utility::IsCameraOut(obj())) {
            obj().model().reqScript(7);
            mWaitFrame = 1;
        }
    }
}

void StateMoveAroundAttack::procMove() {
    const ParamData& param = obj().param().lupa();
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).approachMap();
    if (obj().model().getCurrentScriptIndex() == 7) {
        obj().move().groundDecel(param.mWaitDecel);
    } else {
        obj().move().groundAccel(mIsRight, param.mMoveAccel);
    }
}

void StateMoveAroundAttack::procFixPos() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (t_IsHitWall(obj().mapColl().result())) {
        obj().move().resetSpeedH();
        mIsRight = !mIsRight;
    } else {
        f32 heroX = obj().getBasePos().x;
        f32 diff = obj().location().pos().x - heroX;
        if (hel::math::Math::Abs(diff) > mRange) {
            if ((diff > 0.0f && mIsRight) || (diff < 0.0f && !mIsRight)) {
                mIsRight = !mIsRight;
            }
        }
    }
    if (custom.cliffChecker().isCliff()) {
        obj().move().resetSpeedH();
        mIsRight = !mIsRight;
    }
    custom.cliffChecker().setAccelDirRight(mIsRight);
}

}}}}  // namespace scn::step::enemy::lupa
