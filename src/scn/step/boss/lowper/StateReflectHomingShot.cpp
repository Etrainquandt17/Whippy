#include "scn/step/boss/lowper/StateReflectHomingShot.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWaitFar.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateReflectHomingShot::StateReflectHomingShot(Boss* boss) : StateBase(boss), mCount(0), mPhase(0), _10(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(0x27);
    custom.waftMoveCtrl().setMoveIntpRate(0.5f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
}

StateReflectHomingShot::~StateReflectHomingShot() {
    obj().model().resetScale();
}

void StateReflectHomingShot::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mCount != 0) {
        mCount--;
        if (mCount == 15) {
            Vector3 center = custom.waftMoveCtrl().getCenter();
            switch (mPhase) {
            case 0: {
                center.x = obj().basePos().x - (center.x - obj().basePos().x);
                center.z = -20.0f;
                break;
            }
            case 1:
                center.x = obj().basePos().x;
                center.z = -60.0f;
                break;
            }
            custom.waftMoveCtrl().setCenter(center);
            mPhase++;
        }
        f32 t = mCount / 30.0f;
        f32 rate = 1.0f - Math::AbsF32(Math::CosDegF(180.0f * t));
        Vector3 scale =
            Math::LinearInterpolation(Vector3::ALL_ONE, Vector3(0.01f, 2.0f, 0.01f), rate);
        obj().model().setScale(scale);
    }
    if (obj().scriptTrigger().get(0)) {
        reqShotBullet();
    }
    if (obj().scriptTrigger().get(1)) {
        mCount = 30;
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWaitFar, Boss*>(objPtr());
    }
}

void StateReflectHomingShot::procMove() {}

void StateReflectHomingShot::procFixPos() {}

void StateReflectHomingShot::reqShotBullet() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().request(static_cast<enemy::lowperbullet::VariationKind>(7), obj().location().pos(), Vector3::ZERO, _10);
    _10++;
}

}}}}  // namespace scn::step::boss::lowper
