#define HEL_MATH_VECTOR2_GETNORMALIZED_IN_CLASS
#include "scn/step/boss/goliath/StatePunch.h"

#include "gobj/GearModel.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StatePunch::StatePunch(Boss* boss, f32 elevX, bool isContinue) : StateBase(boss), mAttackFrame(0), mIsContinue(isContinue) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(8);
    custom.elevationCtrl().setElevX(elevX);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().flash().attack().setEnd((GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
}

StatePunch::~StatePunch() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.punchCtrl().resetLength();
    custom.elevationCtrl().resetElev();
}

void StatePunch::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().goliath();
    if (mAttackFrame != 0) {
        mAttackFrame--;
        if (mAttackFrame == 0) {
            obj().objColl().clearAttack(1);
        }
    }
    if (obj().scriptTrigger().get(0)) {
        f32 dist = Math::Abs(custom.landCtrl().getFaceToFaceWallX() - obj().location().pos().x);
        f32 elevX = custom.elevationCtrl().getElevX();
        f32 length = 0.0f;
        f32 cos = Math::CosDegF(elevX);
        if (!Math::EqZero(cos)) {
            length = dist / cos;
        }
        custom.punchCtrl().setLength(length);
    }
    if (obj().scriptTrigger().get(1)) {
        f32 wallX = custom.landCtrl().getFaceToFaceWallX();
        f32 hitX = wallX - 0.02f * obj().target().getSign();
        f32 height = Math::Abs(hitX - obj().location().pos().x);
        Vector2 wallPos(hitX, custom.landCtrl().getFloorYWithBump());
        height *= Math::TanF(0.017453292f * custom.elevationCtrl().getElevX());
        Vector2 hitPos(hitX, 1.5f + (height + obj().location().pos().y));
        if (height < obj().param().goliath()._50 - 1.5f) {
            Vector2 accel = custom.punchCtrl().getGenerateStarSpeedV(height);
            Utility::GenerateStarEffect(obj(), wallPos, hitPos - wallPos, accel, static_cast<map::BinEnemyVariation>(0x19A));
            if (!mIsContinue) {
                custom.punchCtrl().registGenerateStarHeight(height);
            } else {
                custom.punchCtrl().unregistGenerateStarHeight();
            }
        }
        Vector3 effectPos = hitPos.toVector3();
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x283), effectPos);
        effectPos.y += -0.5f;
        effectPos.x += -1.5f * obj().target().getSign();
        obj().effect().normal().requestPD(static_cast<effect::Kind>(0x290), effectPos, obj().target().getDirection3(), 0.6f);
        Vector2 handPos = obj().model().model().nodes().at(5).worldTrans().getXY();
        Vector2 basePos = obj().model().model().nodes().at(1).worldTrans().getXY();
        if (!(handPos - basePos).isZeroLoose(0.00001f)) {
            handPos += (handPos - basePos).getNormalized() * 1.6f;
        }
        obj().objColl().setAttackType(1, static_cast<ocoll::AttackType>(0x1EB));
        obj().objColl().addAttack(1, 0, param._8C, handPos - obj().location().pos().getXY(),
                                  basePos - obj().location().pos().getXY(), false);
        obj().objColl().addAttack(1, 0, param._90, handPos - obj().location().pos().getXY());
        mAttackFrame = 3;
        custom.collisionCtrl().setState(CollisionCtrl::STATE_PUNCH);
    }
    if (obj().scriptTrigger().get(2)) {
        custom.punchCtrl().resetLength();
        custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    }
    if (obj().scriptTrigger().get(3) && !mIsContinue) {
        obj().brainCtrl().toValid();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StatePunch::procMove() {}

void StatePunch::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
