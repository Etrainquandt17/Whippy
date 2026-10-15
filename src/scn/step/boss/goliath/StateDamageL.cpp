#include "scn/step/boss/goliath/StateDamageL.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateAnger.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Manager.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateDamageL::StateDamageL(Boss* boss) : StateBase(boss), mFrame(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().objColl().bodyColl().hit().isCollide()) {
        Vector2 attackPos = obj().objColl().bodyColl().damageInfo().attackPos();
        bool isRight = attackPos.x > obj().location().pos().x;
        obj().target().setIsRightDir(isRight);
        obj().model().rotCtrl().setRotHIntoTarget();
    }
    obj().hitStop().clear();
    obj().model().reqScript(0x22);
    obj().invincible().setPermNoFlash();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    obj().comp().enemyManager().reqDeadAllEnemyForBoss();
    obj().comp().weaponManager().reqDeadByTeamNo(static_cast<ocoll::TeamNo>(1));
    Utility::StagingBossDamageL(obj());
    obj().invincible().setPermNoFlash();
    obj().move().resetVelocity();
    mStartPos = obj().location().pos();
    mGoalPos = obj().location().pos();
    mGoalPos.y = custom.landCtrl().getFloorYWithBump();
    f32 diff = mGoalPos.x - custom.landCtrl().getCenterX();
    f32 limit = 0.5f * custom.landCtrl().getWidth() - 4.0f;
    if (Math::AbsF32(diff) > limit) {
        mGoalPos.x = limit * Math::Sign(diff) + custom.landCtrl().getCenterX();
    }
    obj().model().updateMtx();
}

StateDamageL::~StateDamageL() {}

void StateDamageL::procAnim() {
    mFrame++;
    if (mFrame == 60) {
        obj().soundSE().normal().start(0x367);
    }
    if (obj().scriptTrigger().get(0)) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_REFLECT);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateAnger, Boss*>(objPtr());
    }
}

void StateDamageL::procMove() {
    f32 t = static_cast<f32>(mFrame) / 60.0f;
    if (t > 1.0f) {
        t = 1.0f;
    }
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    pos.y += 3.0f * Math::SinDegF(180.0f * t);
    obj().location().setPos(pos);
}

void StateDamageL::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
