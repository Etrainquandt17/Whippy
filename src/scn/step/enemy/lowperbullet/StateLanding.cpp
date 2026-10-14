#include "scn/step/enemy/lowperbullet/StateLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/lowperbullet/Custom.h"
#include "scn/step/enemy/lowperbullet/ParamData.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {

StateLanding::StateLanding(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().move().resetVelocity();
}

StateLanding::~StateLanding() {}

void StateLanding::procAnim() {
    const ParamData& param = obj().param().lowperbullet();
    mFrame++;
    if (mFrame == param.mLandingFrame) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).requestWeaponLandHit();
        obj().deadWithEffect();
    }
}

void StateLanding::procMove() {}

void StateLanding::procFixPos() {}

}}}}  // namespace scn::step::enemy::lowperbullet
