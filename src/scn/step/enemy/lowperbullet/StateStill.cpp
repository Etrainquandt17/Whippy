#include "scn/step/enemy/lowperbullet/StateStill.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/Water.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/lowperbullet/Custom.h"
#include "scn/step/enemy/lowperbullet/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {

StateStill::StateStill(Enemy* enemy) : StateBase(enemy), mFrame(0), mEndFrame(1), mShakeFrame(0), mBasePos() {
    const ParamData& param = obj().param().lowperbullet();
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().mapColl().setValid(false);
    mBasePos = obj().location().pos();
    mEndFrame = param.mStillFrame + obj().level() * 60;
    obj().hitPoint().set(1);
}

StateStill::~StateStill() {
    obj().mapColl().setValid(true);
}

void StateStill::procAnim() {
    const ParamData& param = obj().param().lowperbullet();
    if (mFrame < mEndFrame) {
        mFrame++;
    } else {
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).requestWeaponBurst();
        obj().deadWithEffect();
        return;
    }
    if (mFrame > mEndFrame - param.mStillShakeFrame) {
        if (mShakeFrame != 0) {
            mShakeFrame--;
        } else {
            mShakeFrame = 4;
            obj().model().shake().request(static_cast<chara::ShakeKind>(3));
        }
    }
}

void StateStill::procMove() {
    const ParamData& param = obj().param().lowperbullet();
    f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param.mStillMoveFrame);
    if (rate > 1.0f) {
        rate = 1.0f;
    }
    hel::math::Vector3 offset;
    offset.x = hel::math::Math::CosDegF(1800.0f * rate);
    offset.y = hel::math::Math::SinDegF(1800.0f * rate);
    offset.z = hel::math::Math::SinDegF(1800.0f * rate);
    offset *= 0.65f * hel::math::Math::CosDegF(90.0f * rate);
    obj().location().setPos(mBasePos + offset);
}

void StateStill::procFixPos() {}

}
}
}
}
