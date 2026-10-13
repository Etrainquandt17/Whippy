#include "scn/step/boss/doubter/StateTornadoRise.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/JugglingCtrl.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/WaftPositionCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateTornadoRise::StateTornadoRise(Boss* boss) : StateBase(boss), mCount(0), mStartY(boss->location().pos().y) {
    obj().footState().setAir();
    obj().guard().setType(static_cast<GuardType>(2));
    obj().model().reqScript(12);
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_3);
    obj().soundSE().loop().start(0x336);
    obj().move().resetVelocity();
}

StateTornadoRise::~StateTornadoRise() {}

void StateTornadoRise::procAnim() {
    mCount++;
    if (mCount == obj().param().doubter()._80) {
        obj().brainCtrl().toValid();
    }
}

void StateTornadoRise::procMove() {
    const Param& param = obj().param().doubter();
    f32 t = (static_cast<f32>(mCount) - static_cast<f32>(param._84)) / static_cast<f32>(param._80 - param._84 * 2);
    f32 rate = 0.5f * (1.0f - hel::math::Math::CosDegF(180.0f * hel::math::Math::LimitMinMax(t, 0.0f, 1.0f)));
    hel::math::Vector3 pos = obj().location().pos();
    pos.y = param._88 * rate + mStartY;
    obj().location().setPos(pos);
}

void StateTornadoRise::procFixPos() {}

}
}
}
}
