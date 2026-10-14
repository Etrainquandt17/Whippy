#include "scn/step/boss/fattybuffer/StateDamageL.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateAnger.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Manager.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateDamageL::StateDamageL(Boss* boss) : StateBase(boss) {
    obj().footState().setAir();
    obj().model().reqScript(0x21);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().comp().enemyManager().reqDeadAllEnemyForBoss();
    obj().comp().weaponManager().reqDeadByTeamNo(ocoll::TEAM_NO_1);
    Utility::StagingBossDamageL(obj());
    obj().invincible().setPermNoFlash();
    obj().move().resetVelocity();
    obj().effect().state().releaseAndVanish();
    obj().effect().normal().releaseAndVanish();
}

StateDamageL::~StateDamageL() {}

void StateDamageL::procAnim() {
    if (obj().model().isAllEnd() && obj().footState().isGround()) {
        obj().stateChanger().setNextState<StateAnger, Boss*>(objPtr());
    }
}

void StateDamageL::procMove() {
    const Param& param = obj().param().fattybuffer();
    if (obj().footState().isGround()) {
        obj().move().groundDecel(param._14);
    } else {
        obj().move().airDecelFall(param._18, param._1C);
    }
}

void StateDamageL::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().footState().setGround();
    }
}

}}}}  // namespace scn::step::boss::fattybuffer
