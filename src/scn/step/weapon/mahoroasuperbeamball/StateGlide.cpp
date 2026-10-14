#include "scn/step/weapon/mahoroasuperbeamball/StateGlide.h"

#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace mahoroasuperbeamball {

StateGlide::StateGlide(Weapon* weapon, const Vector3& targetPos, u32 totalFrame)
    : StateBase(weapon)
    , mStartPos(weapon->location().pos())
    , mTargetPos(targetPos)
    , mTotalFrame(totalFrame)
    , mFrame(0)
    , mShakeInterval(0)
    , mQuakeInterval(0)
    , mIsAttack(false) {
    obj().model().rotCtrl().setValid(false);
    obj().culling().setValid(false);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(7));
}

StateGlide::~StateGlide() {}

void StateGlide::procAnim() {
    if (mFrame < mTotalFrame) {
        mFrame++;
    } else {
        obj().dead();
        return;
    }
    if (mFrame == mTotalFrame / 2) {
        obj().soundSE().start(0x57F);
    }
    if (mShakeInterval != 0) {
        mShakeInterval--;
    } else if (obj().location().pos().z < -50.0f) {
        mShakeInterval = 4;
        obj().model().shake().request(static_cast<chara::ShakeKind>(4));
    } else if (obj().location().pos().z < -30.0f) {
        mShakeInterval = 4;
        obj().model().shake().request(static_cast<chara::ShakeKind>(3));
    }
    if (mQuakeInterval != 0) {
        mQuakeInterval--;
    } else {
        f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(mTotalFrame);
        if (rate >= 0.7f) {
            mQuakeInterval = 4;
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(7));
        } else if (rate >= 0.5f) {
            mQuakeInterval = 4;
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
        } else if (rate >= 0.3f) {
            mQuakeInterval = 4;
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
        }
    }
    bool isAttack = Math::Abs(obj().location().pos().z) < 7.0f;
    if (mIsAttack != isAttack) {
        mIsAttack = isAttack;
        if (isAttack) {
            obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x203));
            obj().objColl().addAttack(0, Utility::IsExtra(obj()) ? 2.5f : 3.0f);
            obj().objColl().setAttackCenter(0, Vector2::ZERO);
        } else {
            obj().objColl().clearAttack();
        }
    }
}

void StateGlide::procMove() {
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTotalFrame);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mTargetPos, t);
    pos.z -= 80.0f
             * (1.0f
                - (1.0f - Math::SinDegF(200.0f * t)) * (1.0f - Math::SinDegF(200.0f * t)));
    obj().location().setPos(pos);
}

void StateGlide::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroasuperbeamball
