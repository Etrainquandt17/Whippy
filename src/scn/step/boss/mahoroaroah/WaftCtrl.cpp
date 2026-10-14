#include "scn/step/boss/mahoroaroah/WaftCtrl.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/mahoroaroah/Param.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjRefHandle.h"

using hel::math::Math;
using hel::math::Vec3;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

namespace {

const Vec3 T_DEFAULT_THETAVEL = { 1.1f, 1.7f, 0.6f };

}

WaftCtrl::WaftCtrl(Boss& boss)
    : mBoss(boss), mRefPos(boss.location().pos()), mTheta(Vector3::ZERO), mThetaVel(T_DEFAULT_THETAVEL), mIsValid(false) {}

WaftCtrl::~WaftCtrl() {}

Vector3 WaftCtrl::getRefPos() const {
    return mRefPos;
}

void WaftCtrl::setRefPos(const Vector3& pos) {
    mRefPos = pos;
}

void WaftCtrl::update() {
    const Param& param = mBoss.param().mahoroaroah();
    if (mIsValid) {
        mTheta += mThetaVel;
        while (mTheta.x >= 360.0f) {
            mTheta.x -= 360.0f;
        }
        while (mTheta.x < 0.0f) {
            mTheta.x += 360.0f;
        }
        while (mTheta.y >= 360.0f) {
            mTheta.y -= 360.0f;
        }
        while (mTheta.y < 0.0f) {
            mTheta.y += 360.0f;
        }
        while (mTheta.z >= 360.0f) {
            mTheta.z -= 360.0f;
        }
        while (mTheta.z < 0.0f) {
            mTheta.z += 360.0f;
        }
        Vector3 pos(Math::SinDegF(mTheta.x), Math::SinDegF(mTheta.y), Math::SinDegF(mTheta.z));
        pos.scale(Vector3(param.mWaftWidth));
        pos += mRefPos;
        mBoss.location().setPos(pos);
    }
}

void WaftCtrl::setToValid() {
    mIsValid = true;
}

}}}}  // namespace scn::step::boss::mahoroaroah
