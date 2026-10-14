#include "scn/step/enemy/shotzo/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/shotzo/Custom.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().brainCtrl().toValid();
}

void StateWait::procMove() {
    const common::ParamData& param = obj().param().common();
    if (!DynamicCastToRef<Custom, ICustom>(obj().custom()).isFixPos() && obj().footState().isAir()) {
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

}}}}  // namespace scn::step::enemy::shotzo
