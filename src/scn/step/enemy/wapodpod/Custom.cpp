#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/wapodpod/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Owner.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/wapod/Custom.h"
#include "scn/step/enemy/wapod/ParamData.h"
#include "scn/step/enemy/wapodpod/StateVomit.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace wapodpod {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mIsExist(false), mIsWait(false), mIsCaptured(false), mIsFixPos(true),
      mWaitFrame(enemy.param().wapod().mPodWaitFrame), mRise(0.0f) {}

bool Custom::onInit() {
    f32 scale = Utility::GetModelScaleBySizeType(obj());
    obj().objColl().clearBodyColl();
    obj().objColl().addBodyColl(0, 0.45f * scale, hel::math::Vector2(0.0f, 0.4f * scale));
    obj().vacuumReceiver().setCustomCollideRect(hel::geo::Rect(0.5f, -0.3f, -0.4f, 0.4f));
    return false;
}

bool Custom::onHitPointIsZero() {
    obj().setPotentialCount(1);
    mIsFixPos = false;
    if (!obj().captureReceiver().isCaptured()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x558), obj().location().pos());
        obj().dead();
        return true;
    }
    return false;
}

bool Custom::onVacuumReceive() {
    return onDamaged();
}

bool Custom::onDamaged() {
    mIsFixPos = false;
    return false;
}

bool Custom::onInWater() {
    obj().soundSE().start(0x2f6);
    return onDamaged();
}

void Custom::onCaptured() {
    mIsFixPos = false;
}

void Custom::onDead() {
    mIsFixPos = false;
}

void Custom::onProcFixPos() {
    bool isCaptured = obj().captureReceiver().isCaptured();
    if (isCaptured) {
        obj().model().anim().setFrameRate(0.0f);
    }
    if (obj().hitPoint().isDead() && mIsCaptured == true && mIsCaptured != isCaptured) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x558), obj().location().pos());
        obj().dead();
        return;
    }
    mIsCaptured = isCaptured;
    fixWapodPos();
    bool isWaitEnd = false;
    if (mWaitFrame <= obj().param().wapod().mPodWaitFrame) {
        mWaitFrame++;
    } else {
        isWaitEnd = true;
    }
    if (isWaitEnd) {
        chara::MapCollResult result = obj().mapColl().result();
        if (result.mIsHitFloor && !mIsExist && mIsWait) {
            obj().stateChanger().setNextState<StateVomit, Enemy*>(&obj());
            mWaitFrame = 0;
            mIsFixPos = true;
            mRise = 0.0f;
        }
    }
}

void Custom::requestWapod() {
    hel::math::Vector2 pos = obj().location().pos().getXY();
    f32 offset = 0.7f;
    if (obj().size() == 1) {
        offset += 0.7f;
    }
    pos.y += offset;
    obj().setPotentialCount(1);
    Desc desc(static_cast<map::BinEnemyKind>(0x81), static_cast<map::BinEnemyVariation>(0x173), obj().level(), obj().dirType(),
              obj().size(), false, false, pos);
    mWapod = obj().comp().enemyManager().request(desc);
    if (mWapod.isAlive()) {
        if (obj().objGenerator() != 0) {
            ogen::Generator& generator = *obj().objGenerator();
            mWapod->setObjGenerator(generator);
        }
        hel::common::DynamicCastToRef<wapod::Custom, ICustom>(mWapod->custom()).setWapodpodUid(obj().objColl().owner().uid());
        mWapod->nururi().setValid(false);
    }
}

bool Custom::reqCustomDeadEffect() {
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x558), obj().location().pos());
    return true;
}

bool Custom::isExist() const {
    return mIsExist;
}

void Custom::setIsExist(bool isExist) {
    mIsExist = isExist;
}

bool Custom::isFixPos() const {
    return mIsFixPos;
}

void Custom::setIsFixPos(bool isFixPos) {
    mIsFixPos = isFixPos;
}

void Custom::setIsWait(bool isWait) {
    mIsWait = isWait;
}

void Custom::fixWapodPos() {
    if (mIsExist && mWapod.isAlive() && mIsFixPos) {
        Enemy* wapod = mWapod.operator->();
        hel::math::Vector3 pos = obj().location().pos();
        mRise += obj().param().wapod().mPodRiseSpeed;
        f32 offset = 0.7f;
        if (obj().size() == 1) {
            offset += 0.7f;
        }
        pos.y += offset + mRise;
        wapod->location().setPos(pos);
    }
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
