#include "scn/step/boss/lowper/StateSprinkler.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateSprinkler::StateSprinkler(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().model().reqScript(0x11);
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.1f);
    custom.dataBuff().shuffleSprinklerBulletSpeedData();
}

StateSprinkler::~StateSprinkler() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).dataBuff().clearSprinklerBulletSpeedData();
}

void StateSprinkler::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        reqBullet();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateSprinkler::procMove() {}

void StateSprinkler::procFixPos() {}

void StateSprinkler::reqBullet() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.dataBuff().isExistSprinklerBulletSpeedData()) {
        Vector3 pos = obj().location().pos();
        Vector3 speed(custom.dataBuff().shiftSprinklerBulletSpeedData(), 0.1f, 0.0f);
        custom.enemyCtrl().request(static_cast<enemy::lowperbullet::VariationKind>(1), pos, speed, 0);
    }
}

}}}}  // namespace scn::step::boss::lowper
