#include "scn/step/enemy/squishy/StateSwim.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/squishy/Custom.h"
#include "scn/step/enemy/squishy/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

StateSwim::StateSwim(Enemy* enemy) : StateBase(enemy), _8(0), mIsLooped(false) {
    const ParamData& param = obj().param().squishy();
    obj().footState().setAir();
    obj().model().reqScript(10);
    obj().model().anim().setFrame(param.mSwimAccelStartFrame);
    obj().move().resetVelocity();
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x133), 0);
    obj().soundSE().start(0x2f5);
}

StateSwim::~StateSwim() {}

void StateSwim::procAnim() {
    const ParamData& param = obj().param().squishy();
    if (obj().model().anim().isLooped()) {
        mIsLooped = true;
    }
    if (mIsLooped && obj().model().anim().frame() >= param.mSwimAccelStartFrame) {
        obj().effect().normal().release();
        obj().move().resetSpeedV();
        obj().brainCtrl().toValid();
    }
}

void StateSwim::procMove() {
    const ParamData& param = obj().param().squishy();
    f32 frame = obj().model().anim().frame();
    if (param.mSwimAccelStartFrame <= frame && frame < param.mSwimAccelEndFrame) {
        obj().model().anim().setFrameRate(param.mSwimFrameRate);
        obj().move().accel(Vector3::BASIS_Y, param.mSwimAccel);
    } else {
        obj().model().anim().setFrameRate(1.0f);
        obj().move().decel(param.mSwimDecel);
    }
}

void StateSwim::procFixPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!custom.isInWater(false)) {
        obj().effect().normal().release();
        obj().move().resetSpeedV();
        custom.setJumpFromWater(true);
        obj().brainCtrl().toValid();
    }
}

}}}}  // namespace scn::step::enemy::squishy
