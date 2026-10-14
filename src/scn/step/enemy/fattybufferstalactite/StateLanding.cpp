#include "scn/step/enemy/fattybufferstalactite/StateLanding.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/fattybufferstalactite/ParamData.h"
#include "snd/SERequestor.h"

using app::Random;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferstalactite {

StateLanding::StateLanding(Enemy* enemy) : StateBase(enemy), mFrame(0), mShakeFrame(0) {
    const ParamData& param = obj().param().fattybufferstalactite();
    obj().footState().setGround();
    obj().move().resetVelocity();
    mFrame = param.mLandFrameBase + Random::RandU32(param.mLandFrameRand);
    mShakeFrame = mFrame - param.mShakeStartFrame;
    if (mShakeFrame < param.mShakeInterval) {
        mShakeFrame = param.mShakeInterval;
    }
    obj().effect().state().requestP(static_cast<effect::Kind>(0x142), obj().location().pos());
    obj().soundSE().start(0x35f);
    obj().model().shake().request(static_cast<chara::ShakeKind>(3));
    obj().model().setViewOffset(Vector3(0.0f, -0.5f, 0.0f));
}

StateLanding::~StateLanding() {
    obj().model().resetViewOffset();
}

void StateLanding::procAnim() {
    const ParamData& param = obj().param().fattybufferstalactite();
    if (mFrame != 0) {
        mFrame--;
    } else {
        obj().deadWithEffect();
        return;
    }
    if (mShakeFrame != 0) {
        mShakeFrame--;
    } else {
        mShakeFrame = param.mShakeInterval;
        obj().model().shake().request(static_cast<chara::ShakeKind>(1));
    }
}

void StateLanding::procMove() {}

void StateLanding::procFixPos() {}

}}}}  // namespace scn::step::enemy::fattybufferstalactite
