#ifndef SCN_STEP_BOSS_ROAH_PARAM_H
#define SCN_STEP_BOSS_ROAH_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "hel/math/Vec3.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

// TODO: the names of the classes are guesses, and so are the types of the members no unit reads. A 3-vector among
// them is a hel::math::Vec3, converted by Vector3(const Vec3&).
struct CollParam {
    f32 mRadius0;
    hel::math::Vec2 mOffset0;
    hel::math::Vec2 mOffset0End;
    f32 mRadius1;
    hel::math::Vec2 mOffset1;
    hel::math::Vec2 mOffset1End;
    f32 mRadius2;
    hel::math::Vec2 mOffset2;
    hel::math::Vec2 mOffset2End;
};

struct LockRectParam {
    f32 mBaseY;
    f32 mHeight;
    f32 mCenterX;
};

struct Param {
    u32 mHitPoint;
    u32 mHitPointExtra;
    f32 mAngryHpRate;
    f32 mAngryHpRateExtra;
    gobj::MoveParamDecel mDecel;
    u32 mOarMoveFrame;
    f32 mOarMoveDistance;
    f32 mHitDepth;
    CollParam mColl;
    CollParam mCollTackle;
    LockRectParam mFirstLockStart;
    LockRectParam mFirstLockGoal;
    LockRectParam mAppearLock;
    f32 mRotMoveMargin;
    f32 mFixRotRate;
    f32 mRotXMax;
    f32 mRotYMax;
    u32 mFirstFrame;
    u32 mAppearMoveFrame;
    u32 mAppearMoveFrameFirst;
    hel::math::Vec2 mFirstOffset;
    f32 mAppearHitX;
    hel::math::Vec3 mAppearEffectOffset;
    f32 mAppearEffectScale;
    f32 mAppearCameraRotY;
    u32 _F8;
    u32 mAppearCameraInFrame;
    u32 mAppearCameraOutFrame;
    hel::math::Vec2 mBulletEffectOffset;
    u32 _10C[(0x114 - 0x10C) / 4];
    f32 mStormAttackRadius;
    f32 mStormAttackRadiusNear;
    f32 mStormAttackLength;
    f32 mStormAttackLengthNear;
    u32 _124;
    f32 mStormRotXMax;
    f32 mStormFixRotRate;
    f32 mStormPhase;
    f32 mStormRotXRate;
    f32 mStormRotZBack;
    f32 mStormRotZSwing;
    u32 mStormDamageTime;
    u32 mStormOnFrame;
    f32 mStormAmplitudeDown;
    f32 mTackleDepth;
    u32 mTackleSEFrame;
    hel::math::Vec2 mTackleEndOffset;
    f32 mTackleEndHitX;
    u32 mTackleEndFrame;
    f32 mPursuitMargin;
    f32 mWaveStarAmplitude;
    hel::math::Vec3 mZStarOffset;
    f32 mZStarCurve;
    f32 mZStarRotY;
    hel::math::Vec3 mZPassStartOffset;
    hel::math::Vec3 mZPassGoalOffset;
    u32 mZPassFrame;
    f32 mZPassCurve;
    hel::math::Vec3 mMahoroaOffsetAppear;
    hel::math::Vec3 mMahoroaOffsetFirst;
    hel::math::Vec3 mMahoroaOffset;
    hel::math::Vec3 mMahoroaEscapeOffsetFirst;
    hel::math::Vec3 mMahoroaEscapeOffsetSecond;
    u32 _1DC;
    f32 mMahoroaMoveRate;
    f32 mMahoroaMoveRateFast;
    u32 mMahoroaAppearFrame;
    f32 mMahoroaAppearSwingX;
    f32 mMahoroaAppearSwingY;
    u32 _1F4;
    u32 mMahoroaEscapeFrame;
    hel::math::Vec3 mMahoroaEscapeWarpOffsetFirst;
    hel::math::Vec3 mMahoroaEscapeWarpOffsetSecond;
    f32 mAppearMahoroaScale;
    u32 mAngerFrame;
    hel::math::Vec3 mDeadOffset;
    f32 mDeadSpeed;
    f32 mDeadSpeedZ;
    f32 mDeadAngle;
    f32 mDeadRotX;
    f32 mDeadRotZ;
    f32 mDeadRotXRate;
    f32 mDeadRotYRate;
    f32 mDeadRotZRate;
};

}}}}  // namespace scn::step::boss::roah

#endif
