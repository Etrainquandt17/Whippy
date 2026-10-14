#include "scn/step/boss/landia/StateDamageL.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/HeadAngleCtrl.h"
#include "scn/step/boss/landia/StateAnger.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Manager.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateDamageL::StateDamageL(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(30);
    custom.waftCtrl().setWaveWidthZero();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().invincible().setPermNoFlash();
    obj().guard().setType(GUARD_TYPE_6);
    obj().comp().enemyManager().reqDeadAllEnemyForBoss();
    obj().comp().weaponManager().reqDeadByTeamNo(static_cast< ::scn::step::ocoll::TeamNo>(1));
    Utility::StagingBossDamageL(obj());
    obj().move().resetVelocity();
    custom.headAngleCtrl().toInvalid();
}

StateDamageL::~StateDamageL() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).headAngleCtrl().toValid();
}

void StateDamageL::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateAnger, Boss*>(objPtr());
    }
}

void StateDamageL::procMove() {}

void StateDamageL::procFixPos() {}

}}}}  // namespace scn::step::boss::landia
