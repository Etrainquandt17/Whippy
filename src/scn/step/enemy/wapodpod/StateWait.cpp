#include "scn/step/enemy/wapodpod/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/wapodpod/Custom.h"

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
