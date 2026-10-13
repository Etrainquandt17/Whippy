#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#include "scn/step/boss/roah/MahoroaCtrl.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Desc.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/mahoroaroah/StateWait.h"
#include "scn/step/boss/mahoroaroah/StateWarp.h"
#include "scn/step/boss/mahoroaroah/WaftCtrl.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

MahoroaCtrl::MahoroaCtrl(Boss& boss)
    : mBoss(boss), mMahoroa(), mPhase(PHASE_11), mAppearCount(0), mEscapeCount(0), mEscapeStart(), mEscapeGoal(), mEscapeWarpCount(0), mPrevCameraX(0.0f) {}

void MahoroaCtrl::init() {
    const Param& param = mBoss.param().roah();
    hel::math::Vector3 pos = mBoss.basePos().toVector3() + (Utility::IsStagingFirstAppear(mBoss) ? hel::math::Vector3(param.mMahoroaOffsetFirst)
                                                                                                 : hel::math::Vector3(param.mMahoroaOffsetAppear));
    Desc desc(static_cast<map::BinBossKind>(0x11), static_cast<map::BinBossVariation>(0), 0, false, pos.getXY(), hel::math::Vector2::ZERO);
    util::ObjRefHandle<Boss> mahoroa = mBoss.comp().bossManager().request(desc);
    if (mahoroa.isAlive()) {
        mahoroa->location().setPos(pos);
        mahoroa->model().setVisibility(false);
        mMahoroa = mahoroa;
        setPhase(PHASE_0);
    }
}

void MahoroaCtrl::update() {
    if (mMahoroa.isAlive()) {
        switch (mPhase) {
        case 0:
            updateWait();
            break;
        case 1:
            updatePursuit();
            break;
        case 2:
        case 3:
            updateWait();
            break;
        case 4:
            updateFirstWarpIn();
            break;
        case 5:
            updateFirstWarpOut();
            break;
        case 6:
            updateAppear();
            break;
        case 7:
        case 8:
            updateEscapeMove();
            break;
        case 9:
            updateEscapeWarpIn();
            break;
        case 10:
            updateEscapeWarpOut();
            break;
        }
    }
}

void MahoroaCtrl::setPhase(Phase phase) {
    mPhase = phase;
    switch (phase) {
    case 0:
    case 1:
    case 6:
        mMahoroa->stateChanger().setNextState<mahoroaroah::StateWait, Boss*>(mMahoroa.operator->());
        break;
    case 2:
    case 4:
        mMahoroa->stateChanger().setNextState<mahoroaroah::StateWarp, Boss*, mahoroaroah::StateWarp::WarpKind>(mMahoroa.operator->(),
                                                                                                                mahoroaroah::StateWarp::WARP_KIND_0);
        break;
    case 9:
        mEscapeWarpCount++;
        mMahoroa->stateChanger().setNextState<mahoroaroah::StateWarp, Boss*, mahoroaroah::StateWarp::WarpKind>(mMahoroa.operator->(),
                                                                                                                mahoroaroah::StateWarp::WARP_KIND_0);
        break;
    case 3:
    case 5:
    case 10:
        mMahoroa->stateChanger().setNextState<mahoroaroah::StateWarp, Boss*, mahoroaroah::StateWarp::WarpKind>(mMahoroa.operator->(),
                                                                                                                mahoroaroah::StateWarp::WARP_KIND_1);
        break;
    case 7:
        initPhaseEscapeMoveFirst();
        mMahoroa->stateChanger().setNextState<mahoroaroah::StateWait, Boss*>(mMahoroa.operator->());
        break;
    case 8:
        initPhaseEscapeMoveSecond();
        mMahoroa->stateChanger().setNextState<mahoroaroah::StateWait, Boss*>(mMahoroa.operator->());
        break;
    }
}

MahoroaCtrl::Phase MahoroaCtrl::getPhase() {
    return mPhase;
}

mahoroaroah::Custom& MahoroaCtrl::getCustom() {
    return hel::common::DynamicCastToRef<mahoroaroah::Custom, ICustom>(mMahoroa->custom());
}

void MahoroaCtrl::setScale(f32 scale) {
    mMahoroa->model().setBaseScale(hel::math::Vector3::ALL_ONE * scale);
}

void MahoroaCtrl::updatePursuit() {
    const Param& param = mBoss.param().roah();
    hel::math::Vector3 pos = mBoss.location().pos() + hel::math::Vector3(param.mMahoroaOffset);
    setPos(pos, param.mMahoroaMoveRateFast);
}

void MahoroaCtrl::updateFirstWarpIn() {
    const Param& param = mBoss.param().roah();
    if (!mMahoroa->model().isVisible()) {
        hel::math::Vector3 pos = mBoss.basePos().toVector3() + hel::math::Vector3(param.mMahoroaOffset);
        setPos(pos, param.mMahoroaMoveRateFast);
    }
}

void MahoroaCtrl::updateFirstWarpOut() {
    const Param& param = mBoss.param().roah();
    hel::math::Vector3 pos = mBoss.basePos().toVector3() + (Utility::IsStagingFirstAppear(mBoss) ? hel::math::Vector3(param.mMahoroaOffsetFirst)
                                                                                                 : hel::math::Vector3(param.mMahoroaOffsetAppear));
    setPos(pos, param.mMahoroaMoveRate);
}

void MahoroaCtrl::updateWait() {
    const Param& param = mBoss.param().roah();
    hel::math::Vector3 pos = mBoss.basePos().toVector3() + hel::math::Vector3(param.mMahoroaOffset);
    setPos(pos, param.mMahoroaMoveRate);
}

void MahoroaCtrl::updateAppear() {
    const Param& param = mBoss.param().roah();
    if (mAppearCount < param.mMahoroaAppearFrame) {
        mAppearCount++;
    }
    hel::math::Vector3 pos = mBoss.basePos().toVector3();
    if (Utility::IsStagingFirstAppear(mBoss)) {
        pos += hel::math::Vector3(param.mMahoroaOffsetFirst);
    } else {
        f32 t = static_cast<f32>(mAppearCount) / static_cast<f32>(param.mMahoroaAppearFrame);
        hel::math::Vector3 from(param.mMahoroaOffsetAppear);
        hel::math::Vector3 to(param.mMahoroaOffset);
        pos.x += hel::math::Math::LinearInterpolation(from.x, to.x, t);
        pos.x += param.mMahoroaAppearSwingX * hel::math::Math::SinDegF(180.0f * t);
        pos.y += hel::math::Math::LinearInterpolation(from.y, to.y, t);
        pos.y -= param.mMahoroaAppearSwingY * hel::math::Math::SinDegF(360.0f * t);
        f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
        pos.z += hel::math::Math::LinearInterpolation(from.z, to.z, rate);
    }
    setPos(pos, param.mMahoroaMoveRate);
}

void MahoroaCtrl::updateEscapeMove() {
    const Param& param = mBoss.param().roah();
    if (mEscapeCount < param.mMahoroaEscapeFrame) {
        mEscapeCount++;
    }
    f32 moved = 0.0f;
    if (!hel::math::Math::EqZero(mPrevCameraX)) {
        moved = mBoss.comp().mainCamera().getCenter().x - mPrevCameraX;
    }
    mPrevCameraX = mBoss.comp().mainCamera().getCenter().x;
    f32 rate = hel::math::Math::SinDegF(90.0f * (static_cast<f32>(mEscapeCount) / static_cast<f32>(param.mMahoroaEscapeFrame)));
    mEscapeStart.x += moved;
    mEscapeGoal.x += moved;
    hel::math::Vector3 pos = hel::math::Math::LinearInterpolation(mEscapeStart, mEscapeGoal, rate);
    setPos(pos, param.mMahoroaMoveRateFast);
}

void MahoroaCtrl::updateEscapeWarpIn() {
    const Param& param = mBoss.param().roah();
    if (!mMahoroa->model().isVisible()) {
        hel::math::Vector3 pos = mBoss.basePos().toVector3() + nextEscapeWarpPos();
        setPos(pos, param.mMahoroaMoveRateFast);
    }
}

void MahoroaCtrl::updateEscapeWarpOut() {
    const Param& param = mBoss.param().roah();
    hel::math::Vector3 pos = mBoss.basePos().toVector3() + nextEscapeWarpPos();
    setPos(pos, param.mMahoroaMoveRateFast);
}

void MahoroaCtrl::setPos(hel::math::Vector3 pos, f32 rate) {
    getCustom().waftCtrl().setRefPos(hel::math::Math::LinearInterpolation(mMahoroa->location().pos(), pos, rate));
}

void MahoroaCtrl::initPhaseEscapeMoveFirst() {
    const Param& param = mBoss.param().roah();
    mEscapeStart = getCustom().waftCtrl().getRefPos();
    mEscapeGoal = mBoss.basePos().toVector3() + hel::math::Vector3(param.mMahoroaEscapeOffsetFirst);
    mEscapeCount = 0;
}

void MahoroaCtrl::initPhaseEscapeMoveSecond() {
    const Param& param = mBoss.param().roah();
    mEscapeStart = getCustom().waftCtrl().getRefPos();
    mEscapeGoal = mBoss.basePos().toVector3() + hel::math::Vector3(param.mMahoroaEscapeOffsetSecond);
    mEscapeCount = 0;
}

hel::math::Vector3 MahoroaCtrl::nextEscapeWarpPos() {
    const Param& param = mBoss.param().roah();
    if (mEscapeWarpCount == 1) {
        return hel::math::Vector3(param.mMahoroaEscapeWarpOffsetFirst);
    }
    return hel::math::Vector3(param.mMahoroaEscapeWarpOffsetSecond);
}

}
}
}
}
