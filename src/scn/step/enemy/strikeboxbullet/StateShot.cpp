#include "scn/step/enemy/strikeboxbullet/StateShot.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/detail/ShapeDiamondContext.h"
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
#include "scn/step/enemy/strikeboxbullet/Custom.h"
#include "scn/step/enemy/strikeboxbullet/ParamData.h"
#include "scn/step/ocoll/AttackType.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace strikeboxbullet {

StateShot::StateShot(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    const ParamData& param = obj().param().strikeboxbullet();
    f32 scale = 1.0f;
    obj().footState().setAir();
    obj().model().rotCtrl().setValid(false);
    obj().objColl().clearBodyColl();
    obj().objColl().addBodyColl(0, 0.4f * scale);
    obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x196));
    obj().mapColl().setValid(false);
}

StateShot::~StateShot() {}

void StateShot::procAnim() {
    const ParamData& param = obj().param().strikeboxbullet();
    mFrame++;
    if (mFrame == param.mCollFrame[obj().level()]) {
        obj().mapColl().setValid(true);
        f32 size = param.mCollSize[obj().level()];
        obj().mapColl().changeActorShape(mcoll::detail::ShapeDiamondContext::CreateBaseCenter(size, size, size));
    }
}

void StateShot::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateShot::procFixPos() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const ParamData& param = obj().param().strikeboxbullet();
    if (mFrame == param.mLifeFrame || obj().mapColl().isHitAll()) {
        obj().effect().state().releaseAndVanish();
        custom.onDamaged();
    }
}

}
}
}
}
