#ifndef SCN_STEP_BOSS_WHISPY_PARAM_H
#define SCN_STEP_BOSS_WHISPY_PARAM_H

#include "hel/math/Vec2.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

// TODO: the names of the classes are guesses, and so are the types of the members no unit reads.
struct VacuumParam {
    u32 mFrame;
    f32 mWindSpeed;
    f32 mWindSpeedMax;
    f32 mWindAccel;
    u32 mEnemyInterval;
    f32 mSearchRadius;
    hel::math::Vec2 mSearchOffset;
    hel::math::Vec2 mSearchOffset2;
};

struct Param {
    u32 mHitPoint;
    u32 mHitPointExtra;
    f32 mAngryHpRate;
    f32 mAngryHpRateExtra;
    f32 mBodyCollRadius;
    hel::math::Vec2 mBodyCollOffset;
    hel::math::Vec2 mBodyCollOffset2;
    u32 mFirstWaitFrame;
    f32 mFirstScrollAccel;
    f32 mFirstScrollSpeedMax;
    f32 mFirstAppearDistance;
    u32 mFallEnemyInterval;
    f32 mAirBallTargetOffsetY;
    hel::math::Vec2 mAirBallOffset;
    hel::math::Vec2 mAirBallSpeed;
    hel::math::Vec3 mAirBallEffectOffset;
    hel::math::Vec2 mAirBallBigOffset;
    hel::math::Vec2 mAirBallBigOffset0;
    hel::math::Vec2 mAirBallBigTarget0;
    hel::math::Vec2 mAirBallBigOffset1;
    hel::math::Vec2 mAirBallBigTarget1;
    hel::math::Vec2 mAirBallBigOffset2;
    hel::math::Vec2 mAirBallBigTarget2;
    hel::math::Vec2 mAirBallBigSpeed;
    hel::math::Vec3 mAirBallBigEffectOffset;
    f32 mTornadoSpeedAdd;
    hel::math::Vec2 mTornadoOffset;
    hel::math::Vec2 mTornadoSpeed;
    hel::math::Vec3 mTornadoEffectOffset;
    VacuumParam mVacuum;
    VacuumParam mVacuumExtra;
    u32 mChewingCount;
    u32 mChewingDamageFirst;
    u32 mChewingDamage;
    u32 mChewingResistPower;
    u32 mGrowFrame;
    f32 mGrowTrunkScale;
    f32 mGrowLockTransX;
    f32 mGrowLockTransY;
    hel::math::Vec3 mGrowBaseTrans;
    hel::math::Vec3 mGrowBaseScale;
    u32 mDeadFrame;
    hel::math::Vec3 mDeadMove;
    hel::math::Vec3 mDeadStagingOffset;
    hel::math::Vec3 mDeadShipPartsOffset;
    hel::math::Vec2 mDeadShipPartsGoal;
    hel::math::Vec3 mDeadClearDanceOffset;
    f32 mFirstWorldRect[4];
    f32 mLockRect[4];
    hel::math::Vec3 mCaptureOffset;
};

}}}}  // namespace scn::step::boss::whispy

#endif
