#include "scn/step/boss/goliath/StateBlizzard.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateBlizzard::StateBlizzard(Boss* boss, const BlizzardDesc& desc) : StateBase(boss), mIndex(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    addBlizzardReqData(desc._0, false);
    addBlizzardReqData(desc._4, false);
    addBlizzardReqData(desc._8, false);
    if (desc._10) {
        addBlizzardReqData(desc._C, false);
        addBlizzardReqData(desc._8, true);
        addBlizzardReqData(desc._4, true);
        addBlizzardReqData(desc._0, true);
    }
    Utility::ControlHateOnAction(obj());
    if (desc._10) {
        obj().model().reqScript(0x1C);
    } else {
        obj().model().reqScript(0x1B);
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(GUARD_TYPE_1);
}

StateBlizzard::~StateBlizzard() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).elevationCtrl().resetElev();
}

void StateBlizzard::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        const BlizzardReqData& data = mReqData[mIndex];
        custom.elevationCtrl().setElevZ(data.mAngle);
    }
    if (obj().scriptTrigger().get(1)) {
        f32 angle = mReqData[mIndex].mAngle;
        Vector2 pos = obj().location().pos().getXY();
        pos.x += 3.0f * (obj().target().getSign() * Math::CosDegF(angle));
        pos.y += 3.0f * Math::SinDegF(angle);
        pos.y += 1.5f;
        Vector2 speed;
        speed.x = 0.3f * (obj().target().getSign() * Math::CosDegF(angle));
        speed.y = 0.3f * Math::SinDegF(angle);
        Vector2 accel = Vector2::BASIS_Y;
        if (mReqData[mIndex].mIsReverse) {
            accel.y *= -1.0f;
        }
        weapon::Desc desc(static_cast<weapon::Kind>(0x44), 0, static_cast<ostop::Flag>(8), pos, speed, obj().objColl().owner());
        desc._24 = accel;
        obj().comp().weaponManager().request(desc);
        mIndex++;
        if (mIndex >= mReqData.count()) {
            mIndex = mReqData.count() - 1;
        }
    }
    if (obj().scriptTrigger().get(2)) {
        custom.elevationCtrl().resetElev();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateBlizzard::procMove() {}

void StateBlizzard::procFixPos() {}

void StateBlizzard::addBlizzardReqData(f32 angle, bool isReverse) {
    BlizzardReqData data;
    data.mAngle = angle;
    data.mIsReverse = isReverse;
    mReqData.add(data);
}

}}}}  // namespace scn::step::boss::goliath
