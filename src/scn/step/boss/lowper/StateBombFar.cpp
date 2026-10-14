#include "scn/step/boss/lowper/StateBombFar.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/DataBuff.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateBombFar::StateBombFar(Boss* boss) : StateBase(boss), mPos(), mCount(0), mIsStarted(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    obj().model().reqScript(0x10);
    mPos = obj().basePos().toVector3();
    mPos.y += 2.0f;
    mPos.z -= 80.0f;
    obj().model().rotCtrl().setRotHTarget(0.0f);
    Vector3 center = obj().basePos().toVector3();
    center.y += 2.0f;
    center.z += -80.0f;
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(center);
}

StateBombFar::~StateBombFar() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.dataBuff().clearBombFarBulletData();
}

void StateBombFar::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mIsStarted) {
        mCount++;
    }
    if (obj().scriptTrigger().get(0)) {
        mIsStarted = true;
    }
    if (mIsStarted) {
        u32 count = custom.dataBuff().countBombFarBulletData();
        for (u32 i = 0; i < count; i++) {
            DataBuff::BombFarBulletData data = custom.dataBuff().getBombFarBulletData(i);
            if (mCount == data._4) {
                reqBomb(data._0);
            }
        }
    }
    if (mCount == custom.dataBuff().getMaxIntervalBombFarBulletData() + 60) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateBombFar::procMove() {}

void StateBombFar::procFixPos() {}

void StateBombFar::reqBomb(f32 speedX) {
    Vector3 pos = obj().location().pos();
    pos.y += 0.25f;
    Vector3 speed(speedX, 0.12f, 0.0f);
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().request(static_cast<enemy::lowperbullet::VariationKind>(2), pos, speed, 0);
}

}}}}  // namespace scn::step::boss::lowper
