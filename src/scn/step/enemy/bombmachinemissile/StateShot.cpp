#include "scn/step/enemy/bombmachinemissile/StateShot.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
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
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/bombmachinemissile/Custom.h"
#include "scn/step/enemy/bombmachinemissile/ParamData.h"
#include "scn/step/ocoll/AttackType.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace bombmachinemissile {

StateShot::StateShot(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    const ParamData& param = obj().param().bombmachinemissile();
    f32 scale = 1.0f;
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().model().rotCtrl().setValid(false);
    obj().model().setCustomMtx(hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3::BASIS_Y,
                                                                     obj().move().velocity().x > 0.0f ? 90.0f : -90.0f));
    if (obj().level() == 1) {
        scale = param.mSuperScale;
        obj().model().setBaseScale(hel::math::Vector3::ALL_ONE * scale);
        hel::math::Vector3 pos = obj().location().pos();
        pos.x += obj().move().velocity().x > 0.0f ? 1.0f : -1.0f;
        pos.y += -0.4f;
        obj().location().setPos(pos);
        obj().vacuumReceiver().setResistLevelStep(1);
        obj().setVacuumedCount(2);
    }
    obj().objColl().clearBodyColl();
    obj().objColl().addBodyColl(1, 0.4f * scale);
    obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x19d));
    obj().soundSE().start(0x2cc);
}

StateShot::~StateShot() {}

void StateShot::procAnim() {
    const ParamData& param = obj().param().bombmachinemissile();
    u32 frame = obj().level() == 1 ? param.mEffectFrameSuper : param.mEffectFrame;
    if (++mFrame == frame) {
        obj().effect().state().requestN(static_cast<effect::Kind>(0x47e), 1);
    }
}

void StateShot::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateShot::procFixPos() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const ParamData& param = obj().param().bombmachinemissile();
    if (mFrame == param.mLifeFrame || obj().mapColl().isHitAll()) {
        obj().effect().state().releaseAndVanish();
        custom.onDamaged();
    }
}

}
}
}
}
