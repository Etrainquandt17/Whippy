#include "scn/step/enemy/lowperbullet/StateHoming.h"

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

StateHoming::StateHoming(Enemy* enemy) : StateBase(enemy), mFrame(0), mDir(-hel::math::Vector3::BASIS_Y) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    if (!obj().move().velocity().isZeroLoose(0.00001f)) {
        mDir = obj().move().velocity().getNormalized();
    }
}

StateHoming::~StateHoming() {}

void StateHoming::procAnim() {
    const ParamData& param = obj().param().lowperbullet();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().water().isInWater()) {
        obj().move().setMoveRate(param.mWaterMoveRate);
    } else {
        obj().move().resetMoveRate();
    }
    mFrame++;
    if (mFrame == param.mHomingFrame - 10) {
        obj().model().shake().request(static_cast<chara::ShakeKind>(3));
    }
    if (mFrame == param.mHomingFrame) {
        hel::math::Vector3 target = custom.getTargetHeroPos();
        hel::math::Vector3 dir = target - obj().location().pos();
        if (!dir.isZeroLoose(0.00001f)) {
            mDir = dir.getNormalized();
        }
    }
}

void StateHoming::procMove() {
    const ParamData& param = obj().param().lowperbullet();
    if (mFrame > param.mHomingFrame) {
        const gobj::MoveParamAccel& accel = Utility::IsExtra(obj()) ? param.mHomingAccelExtra : param.mHomingAccel;
        obj().move().accel(mDir, accel);
    } else {
        obj().move().decel(param.mHomingDecel);
    }
}

void StateHoming::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHit()) {
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).requestWeaponLandHit();
        obj().deadWithEffect();
    }
}

}}}}  // namespace scn::step::enemy::lowperbullet
