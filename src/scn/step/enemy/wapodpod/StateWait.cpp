#include "scn/step/enemy/wapodpod/StateWait.h"

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
#include "scn/step/enemy/wapodpod/Custom.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace wapodpod {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setIsWait(true);
    obj().footState().setGround();
    obj().brainCtrl().toValid();
}

StateWait::~StateWait() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setIsWait(false);
}

void StateWait::procMove() {
    if (obj().footState().isAir()) {
        const common::ParamData& param = obj().param().common();
        obj().move().airDecelFall(param.mDecel, param.mFall);
    } else {
        obj().move().resetSpeedV();
    }
}

void StateWait::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().footState().setGround();
    } else {
        obj().footState().setAir();
    }
}

}}}}  // namespace scn::step::enemy::wapodpod
