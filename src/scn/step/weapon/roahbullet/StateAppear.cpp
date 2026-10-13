#include "scn/step/weapon/roahbullet/StateAppear.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahbullet/Custom.h"
#include "scn/step/weapon/roahbullet/Param.h"
#include "scn/step/weapon/roahbullet/StateWait.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

StateAppear::StateAppear(Weapon* weapon) : StateBase(weapon), mWaitFrame(0), mFrame(0) {
    obj().model().reqScript(0);
    mStartPos = obj().location().pos();
    mEndPos = mStartPos + obj().move().velocity();
}

void StateAppear::procAnim() {
    const Param& param = obj().param().roahBullet();
    if (mWaitFrame < 6 - hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).generateNum()) {
        mWaitFrame++;
    } else if (mFrame < param._8) {
        mFrame++;
        if (mFrame == 1) {
            obj().setVisibility(true);
            switch (obj().variation()) {
            case 0:
                obj().effect().normal().requestN(static_cast<effect::Kind>(0x4C5), 1);
                break;
            case 1:
                obj().effect().normal().requestN(static_cast<effect::Kind>(0x4C3), 1);
                break;
            case 2:
                obj().effect().normal().requestN(static_cast<effect::Kind>(0x4C7), 1);
                break;
            }
        }
    } else {
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1FA));
        obj().objColl().addAttack(0, param._0);
        obj().objColl().addHit(0, param._4);
        obj().stateChanger().setNextState<StateWait, Weapon*>(&obj());
    }
}

void StateAppear::procMove() {
    const Param& param = obj().param().roahBullet();
    f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param._8);
    hel::math::Vector3 pos = hel::math::Math::LinearInterpolation(mStartPos, mEndPos, rate);
    f32 t = hel::math::Math::InterpolationParamMinToMin(rate);
    hel::math::Vector3 offset = pos - mStartPos;
    offset.rotate(hel::math::Vector3::AXIS_X, 0.017453292f * (360.0f * t));
    offset.z *= param._C;
    hel::math::Vector3 newPos = mStartPos + offset;
    obj().location().setPos(newPos);
}

void StateAppear::procFixPos() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).procFixPos();
}

}}}}  // namespace scn::step::weapon::roahbullet
