#include "scn/step/enemy/lowperbullet/StateLanding.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/lowperbullet/Custom.h"
#include "scn/step/enemy/lowperbullet/ParamData.h"
#include "snd/SERequestor.h"

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
