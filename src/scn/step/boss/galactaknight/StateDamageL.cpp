#include "scn/step/boss/galactaknight/StateDamageL.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/StateAnger.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/BGMController.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Manager.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateDamageL::StateDamageL(Boss* boss) : StateBase(boss), mCount(0), mStartPos(boss->location().pos()), mGoalPos() {
    const Param& param = obj().param().galactaknight();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().objColl().bodyColl().hit().isCollide()) {
        Vector2 attackPos = obj().objColl().bodyColl().damageInfo().attackPos();
        bool isRight = attackPos.x > obj().location().pos().x;
        obj().target().setIsRightDir(isRight);
    }
    obj().hitStop().clear();
    obj().comp().enemyManager().reqDeadAllEnemyForBoss();
    obj().comp().weaponManager().reqDeadByTeamNo(static_cast<ocoll::TeamNo>(1));
    Utility::StagingBossDamageL(obj());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_REFLECT);
    obj().invincible().setPermNoFlash();
    mGoalPos.x = param._128 * -obj().target().getSign() + mStartPos.x;
    mGoalPos.y = custom.landCtrl().getFloorY();
    mGoalPos.z = 0.0f;
    obj().model().reqScript(0x29);
    obj().comp().bgmController().pause(static_cast<core::BGMCategory>(1));
}

StateDamageL::~StateDamageL() {}

void StateDamageL::procAnim() {
    const Param& param = obj().param().galactaknight();
    if (mCount < param._124) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateAnger, Boss*>(objPtr());
    }
}

void StateDamageL::procMove() {
    const Param& param = obj().param().galactaknight();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._124);
    f32 sin = Math::SinDegF(180.0f * t);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    pos.y += param._12C * sin;
    obj().location().setPos(pos);
}

void StateDamageL::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
