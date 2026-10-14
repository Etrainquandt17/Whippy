#include "scn/step/enemy/lowperbullet/StateShotBullet.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Water.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/lowperbullet/Custom.h"
#include "scn/step/enemy/lowperbullet/ParamData.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {

StateShotBullet::StateShotBullet(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(0);
}

StateShotBullet::~StateShotBullet() {}

void StateShotBullet::procAnim() {
    const ParamData& param = obj().param().lowperbullet();
    if (obj().water().isInWater()) {
        obj().move().setMoveRate(param.mWaterMoveRate);
    } else {
        obj().move().resetMoveRate();
    }
}

void StateShotBullet::procMove() {
    const ParamData& param = obj().param().lowperbullet();
    obj().move().decel(param.mShotDecel);
}

void StateShotBullet::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHit()) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).requestWeaponLandHit();
        obj().deadWithEffect();
    }
}

}}}}  // namespace scn::step::enemy::lowperbullet
