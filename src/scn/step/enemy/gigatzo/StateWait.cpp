#include "scn/step/enemy/gigatzo/StateWait.h"

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
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/gigatzo/Custom.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace gigatzo {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isBackAttack() || custom.isAir()) {
        obj().footState().setAir();
    } else {
        obj().footState().setGround();
    }
    obj().model().reqScript(0);
    custom.setWaitEffect();
    obj().brainCtrl().toValid();
}

StateWait::~StateWait() {
    obj().effect().normal().release();
}

void StateWait::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().footState().isAir() && !custom.isBackAttack() && !custom.isAir()) {
        obj().move().airDecelFall(obj().param().common().mDecel, obj().param().common().mFall);
    } else {
        obj().move().resetSpeedV();
    }
}

void StateWait::procFixPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!custom.isBackAttack() && !custom.isAir()) {
        if (obj().mapColl().result().mIsHitFloor) {
            obj().footState().setGround();
        } else {
            obj().footState().setAir();
        }
    }
}

}}}}  // namespace scn::step::enemy::gigatzo
