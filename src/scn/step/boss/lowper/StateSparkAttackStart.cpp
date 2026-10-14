#include "scn/step/boss/lowper/StateSparkAttackStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "pow.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateSparkAttack.h"
#include "scn/step/boss/lowper/StateSparkAttackRolling.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

using hel::common::DynamicCastToRef;
using hel::geo::Rect;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateSparkAttackStart::StateSparkAttackStart(Boss* boss, u32 frame, u32 _3, f32 y, bool isRolling)
    : StateBase(boss), mFrame(frame), mCount(0), _10(_3), mStartPos(), mGoalPos(), mIsRolling(isRolling) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Utility::ControlHateOnAction(obj());
    Rect rect = obj().comp().mainCamera().getViewRect();
    f32 width = Math::AbsF32(rect._C - rect._8);
    f32 sign = Math::SignF32(obj().location().pos().x - obj().basePos().x);
    mStartPos = obj().location().pos();
    mGoalPos.x = obj().basePos().x + sign * (0.5f * width - 0.5f);
    mGoalPos.y = y + obj().basePos().y;
    obj().model().reqScript(0x1C);
    obj().guard().setType(static_cast<GuardType>(1));
}

StateSparkAttackStart::~StateSparkAttackStart() {
    obj().objColl().clearAttack(1);
}

void StateSparkAttackStart::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else if (mIsRolling) {
        obj().stateChanger().setNextState<StateSparkAttackRolling, Boss*, unsigned long>(objPtr(), _10);
    } else {
        obj().stateChanger().setNextState<StateSparkAttack, Boss*, unsigned long>(objPtr(), _10);
    }
}

void StateSparkAttackStart::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    Vector3 pos(
        Math::LinearInterpolation(mStartPos.x, mGoalPos.x, t * t),
        Math::LinearInterpolation(mStartPos.y, mGoalPos.y, 1.0f - POW2(1.0f - Math::SinDegF(90.0f * t))),
        Math::LinearInterpolation(mStartPos.z, mGoalPos.z, t)
    );
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.waftMoveCtrl().setMoveIntpRate(0.5f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateSparkAttackStart::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
