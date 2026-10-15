#define MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE
#define SCN_STEP_GIMMICK_MANAGER_SWITCHRECEIVERMANAGER_IN_CLASS

#include "scn/step/boss/goliath/StateGroundChange.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateGroundChangeLanding.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/gimmick/Manager.h"
#include "scn/step/gimmick/SwitchReceiverManager.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateGroundChange::StateGroundChange(Boss* boss) : StateBase(boss), mLevel(0), mFrame(0) {
    const Param& param = obj().param().goliath();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x17);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(GUARD_TYPE_5);
    obj().hitStop().setArmor();
    mLevel = custom.landCtrl().getLevel();
    int num = static_cast<int>(custom.landCtrl().getWidth() / 4.0f) + 1;
    f32 step = custom.landCtrl().getWidth() / static_cast<f32>(num + 1);
    Vector3 pos(custom.landCtrl().getCenterX() - 0.5f * custom.landCtrl().getWidth(),
                0.5f * (custom.landCtrl().getFloorY() + custom.landCtrl().getFloorYWithBump()), 0.0f);
    for (int i = 0; i < num; i++) {
        pos.x += step;
        obj().effect().fore().requestP(static_cast<effect::Kind>(0x1DB), pos);
    }
    obj().soundSE().normal().start(0x36B);
    mStartPos = obj().location().pos();
    custom.landCtrl().levelUp();
    mGoalPos = mStartPos;
    mGoalPos.y = custom.landCtrl().getFloorYWithBump();
    f32 diff = mGoalPos.x - custom.landCtrl().getCenterX();
    f32 limit = 0.5f * custom.landCtrl().getWidth() - 2.5f;
    if (Math::AbsF32(diff) > limit) {
        mGoalPos.x = limit * Math::Sign(diff) + custom.landCtrl().getCenterX();
    }
    obj().comp().gimmickManager().switchReceiverManager().onSwitchOn(mLevel);
    custom.cameraCtrl().startGroundChange(90);
}

StateGroundChange::~StateGroundChange() {}

void StateGroundChange::procAnim() {
    if (mFrame < 90) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateGroundChangeLanding, Boss*>(objPtr());
    }
}

void StateGroundChange::procMove() {
    f32 t = static_cast<f32>(mFrame) / 90.0f;
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    pos.y += 6.0f * Math::SinDegF(180.0f * t);
    obj().location().setPos(pos);
}

void StateGroundChange::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
