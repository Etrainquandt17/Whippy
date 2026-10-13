#include "scn/step/boss/whispy/StateDead.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/ArenaCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/whispy/Custom.h"
#include "scn/step/boss/whispy/Param.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/weapon/Manager.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateDead::StateDead(Boss* boss) : StateBase(boss), mCount(0), mIsStaged(false), mStartPos(boss->location().pos()) {
    obj().objColl().bodyColl().setStateXlu();
    stagingBossDead();
}

StateDead::~StateDead() {}

void StateDead::procAnim() {
    const Param& param = obj().param().whispy();
    if (!mIsStaged) {
        stagingBossDead();
        return;
    }
    if (mCount < param.mDeadFrame) {
        mCount++;
        if (mCount == 1) {
            Utility::DisappearBossPanel(obj());
        }
        if (mCount == param.mDeadFrame) {
            if (Utility::IsArena(obj())) {
                obj().comp().bossManager().arenaCtrl().setNextScene(true);
                return;
            }
            Utility::GenerateShipParts(obj(), static_cast<item::ShipPartKind>(0),
                                       obj().location().pos() + hel::math::Vector3(param.mDeadShipPartsOffset),
                                       obj().basePos() + hel::math::Vector2(param.mDeadShipPartsGoal));
            obj().comp().heroManager().setClearDanceOffset(4, hel::math::Vector3(param.mDeadClearDanceOffset));
        }
    }
    f32 rate = static_cast<f32>(mCount) / static_cast<f32>(param.mDeadFrame);
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 trunkScale = hel::math::Math::LinearInterpolation(param.mGrowTrunkScale, 1.0f, rate);
    custom.tsctrl().setTrunkScale(trunkScale);
    hel::math::Vector3 trans = hel::math::Vector3(param.mGrowBaseTrans) * (1.0f - rate);
    custom.tsctrl().setBaseTrans(trans);
    obj().location().setPos(obj().location().pos() + hel::math::Vector3::BASIS_Z * (param.mGrowBaseTrans.z - trans.z));
    hel::math::Vector3 scale =
        hel::math::Math::LinearInterpolation(hel::math::Vector3(param.mGrowBaseScale), hel::math::Vector3::ALL_ONE, rate);
    custom.tsctrl().setBaseScale(scale);
    obj().location().setPos(mStartPos + hel::math::Vector3(param.mDeadMove) * (rate * rate));
}

void StateDead::procMove() {}

void StateDead::procFixPos() {}

void StateDead::stagingBossDead() {
    const Param& param = obj().param().whispy();
    if (!mIsStaged && !Utility::IsHeroDeadStop(obj())) {
        mIsStaged = true;
        obj().comp().enemyManager().reqDeadAllEnemyForBoss();
        obj().comp().weaponManager().reqDeadByTeamNo(ocoll::TEAM_NO_1);
        obj().model().reqScript(0x15);
        Utility::StagingBossDead(obj(), hel::math::Vector3(param.mDeadStagingOffset));
    }
}

}}}}  // namespace scn::step::boss::whispy
