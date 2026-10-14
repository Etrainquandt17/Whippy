#include "scn/step/boss/metalgeneral/StateDamageL.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Gear.h"
#include "scn/step/boss/GearManager.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/StateAnger.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Manager.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateDamageL::StateDamageL(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0xD);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_REFLECT);
    obj().invincible().setPermNoFlash();
    obj().guard().setType(static_cast<GuardType>(6));
    obj().comp().enemyManager().reqDeadAllEnemyForBoss();
    obj().comp().weaponManager().reqDeadByTeamNo(ocoll::TEAM_NO_1);
    Utility::StagingBossDamageL(obj());
    obj().move().resetVelocity();
    obj().gearManager().gear(0).setVisibility(false);
    obj().mapColl().setValid(true);
}

StateDamageL::~StateDamageL() {}

void StateDamageL::procAnim() {
    if (obj().model().isAllEnd() && obj().footState().isGround()) {
        obj().stateChanger().setNextState<StateAnger, Boss*>(objPtr());
    }
}

void StateDamageL::procMove() {
    const Param& param = obj().param().metalgeneral();
    if (obj().footState().isGround()) {
        obj().move().groundDecel(param._1C);
    } else {
        obj().move().airDecelFall(param._20, param._24);
    }
}

void StateDamageL::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().footState().setGround();
    }
}

}}}}  // namespace scn::step::boss::metalgeneral
