#include "scn/step/enemy/needlous/StateIdling.h"

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
#include "scn/step/enemy/needlous/Custom.h"
#include "scn/step/enemy/needlous/ParamData.h"
#include "scn/step/enemy/needlous/StateAttack.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace needlous {

StateIdling::StateIdling(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().objColl().clearBodyColl();
    f32 radius = 0.4f * Utility::GetModelScaleBySizeType(obj());
    obj().objColl().addBodyColl(2, radius);
    obj().model().reqScript(7);
    if (custom.isIdlingTurn()) {
        obj().footState().setGround();
        obj().model().rotCtrl().setValid(false);
    } else {
        obj().footState().setAir();
    }
    obj().brainCtrl().toValid();
}

StateIdling::~StateIdling() {
    obj().model().rotCtrl().setValid(true);
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setIdlingTurn(false);
    obj().move().resetSpeedH();
}

void StateIdling::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (++mFrame == 10) {
        obj().model().rotCtrl().setValid(true);
        custom.setIdlingTurn(false);
    }
}

void StateIdling::procMove() {
    const ParamData& param = obj().param().needlous();
    obj().move().airDecelFall(obj().param().needlous().mDecel, param.mFall);
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).runSE();
}

void StateIdling::procFixPos() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const ParamData& param = obj().param().needlous();
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor && obj().model().anim().frame() >= 1.0f) {
        f32 speed = obj().move().velocity().y;
        if (hel::math::Math::Abs(speed) >= param.mIdlingBoundMin) {
            obj().soundSE().start(0x2bc);
        }
        speed *= param.mIdlingBoundRate;
        if (hel::math::Math::Abs(speed) < param.mIdlingBoundMin) {
            speed = 0.0f;
            custom.runSE();
        }
        obj().move().setSpeedV(-speed);
        custom.smoke();
    } else if (!result.mIsHitFloor && obj().footState().isGround()) {
        obj().footState().setAir();
    }
    if (result._2) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (mFrame > obj().param().needlous().mIdlingFrame && 0.0f == hel::math::Math::Abs(obj().move().velocity().y)) {
        obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::needlous
