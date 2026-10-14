#include "scn/step/boss/lowper/StateVortex.h"

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

StateVortex::StateVortex(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().model().reqScript(0x24);
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.1f);
    custom.dataBuff().shuffleVortexBulletSpeedData();
}

StateVortex::~StateVortex() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).dataBuff().clearVortexBulletSpeedData();
}

void StateVortex::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        reqBullet();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateVortex::procMove() {}

void StateVortex::procFixPos() {}

void StateVortex::reqBullet() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.dataBuff().isExistVortexBulletSpeedData()) {
        Vector3 pos = obj().location().pos();
        Vector3 speed(custom.dataBuff().shiftVortexBulletSpeedData(), 0.0f, 0.0f);
        custom.enemyCtrl().request(static_cast<enemy::lowperbullet::VariationKind>(6), pos, speed, 0);
    }
}

}}}}  // namespace scn::step::boss::lowper
