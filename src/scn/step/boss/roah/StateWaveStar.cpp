#include "scn/step/boss/roah/StateWaveStar.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateWaveStar::StateWaveStar(Boss* boss, Config config) : StateBase(boss), mCount(0), mBasePos(), mConfig(config) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().brainCtrl().toValid();
    obj().move().resetVelocity();
    obj().effect().state().requestN(static_cast<effect::Kind>(0x4CA), 3);
    mBasePos = obj().location().pos().getXY();
}

StateWaveStar::~StateWaveStar() {}

void StateWaveStar::procAnim() {
    mCount++;
    if (mCount == mConfig._0) {
        mCount = 0;
    }
    if (obj().scriptTrigger().get(0)) {
        obj().soundSE().normal().start(0x461);
    }
}

void StateWaveStar::procMove() {
    const Param& param = obj().param().roah();
    if (Utility::IsVariationExtra(obj())) {
        f32 rate = static_cast<f32>(mCount) / static_cast<f32>(mConfig._0);
        hel::math::Vector2 pos = mBasePos;
        pos.y += param.mWaveStarAmplitude * hel::math::Math::SinDegF(360.0f * rate);
        obj().location().setPos(pos.toVector3());
    }
}

void StateWaveStar::procFixPos() {}

}
}
}
}
