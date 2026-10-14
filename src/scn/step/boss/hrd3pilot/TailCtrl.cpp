#include "scn/step/boss/hrd3pilot/TailCtrl.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/chara/Model.h"

using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

namespace {

const f32 T_STORAGE_SCALE = 0.3f;

}

TailCtrl::TailCtrl(Boss& boss) : mBoss(boss), mIsStored(false), mCount(0) {}

void TailCtrl::update() {
    if (mIsStored) {
        if (mCount < 30) {
            mCount++;
        } else {
            return;
        }
    } else {
        if (mCount != 0) {
            mCount--;
        } else {
            return;
        }
    }
    if (mCount == 30 && mIsStored) {
        mBoss.effect().normal().release();
    }
    f32 t = (f32)mCount / 30.0f;
    f32 scale = Math::LinearInterpolation(1.0f, T_STORAGE_SCALE, t);
    Matrix34 mtx = Matrix34::CreateScale(Vector3(1.0f, scale, 1.0f));
    mBoss.model().model().nodes().at(6).localMtx().setRTMtx(mtx);
}

void TailCtrl::storage() {
    mIsStored = true;
}

void TailCtrl::extract() {
    if (mIsStored) {
        mIsStored = false;
        mBoss.effect().normal().requestN(static_cast<effect::Kind>(0x459), 5);
    }
}

}}}}  // namespace scn::step::boss::hrd3pilot
