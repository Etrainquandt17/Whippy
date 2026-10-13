#ifndef SCN_STEP_BOSS_LANDIA_PARAM_H
#define SCN_STEP_BOSS_LANDIA_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "hel/math/Vec3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

// TODO: the names are guesses, and so are the types of the members no unit reads.
struct Param {
    u32 _0[0x1C / 4];
    gobj::MoveParamDecel mDecel;
    f32 mBaseHeight;
    f32 _24;
    f32 _28;
    u32 mHowlStopFrame;
    f32 _30;
    f32 _34;
    f32 _38;
    u32 _3C[(0xF4 - 0x3C) / 4];
    f32 mHeadOffsetY;
    f32 mNeckAngleRate;
    f32 mNeckAngleMax;
    f32 mNeckAngleMin;
    f32 mHeadDistance;
    f32 mHeadAngleRate;
    f32 mHeadAngleMax;
    f32 mHeadAngleMin;
    f32 mWaftWidthRate;
    hel::math::Vec2 mWaftWidth;
    f32 mWaftThetaVel;
    hel::math::Vec2 _124;
    f32 _12C;
    u32 _130;
    u32 _134;
    hel::math::Vec3 _138;
    f32 _144;
    f32 _148;
    f32 _14C;
    u32 _150;
    u32 _154;
    f32 _158;
    f32 _15C;
    f32 _160;
    u32 _164;
    u32 _168;
    u32 _16C;
    f32 _170;
    f32 _174;
    u32 _178;
    u32 _17C;
    f32 _180;
    u32 _184;
    u32 _188;
    u32 mGlideStartFrame;
    f32 mGlideStartSwing;
    f32 mGlideStartOffsetX;
    f32 mGlideStartOffsetY;
    u32 _19C;
    u32 _1A0;
    u32 _1A4;
    f32 _1A8;
    f32 _1AC;
    f32 _1B0;
    f32 _1B4;
    f32 _1B8;
    f32 _1BC;
    f32 _1C0;
    u32 _1C4;
    f32 _1C8;
    f32 _1CC;
    f32 _1D0;
    f32 _1D4;
    f32 _1D8;
    f32 _1DC;
    u32 mGlideEndFrame;
    f32 mGlideEndOffsetX;
    f32 mGlideEndOffsetY;
    f32 _1EC;
    f32 _1F0;
    f32 _1F4;
    u32 mWindCutterTurnWaitFrame;
    u32 mWindCutterTurnFrame;
    u32 _200;
    f32 mWindCutterTurnSwingY;
    f32 mWindCutterTurnSwingZ;
    u32 mTailStartFrame;
    f32 mTailStartDistance;
    f32 mTailStartHeight;
    u32 _218;
    f32 _21C;
    f32 _220;
    f32 _224;
    f32 _228;
    u32 _22C;
    u32 _230;
    f32 _234;
    f32 _238;
    f32 _23C;
    f32 mTwinBreathMoveSwing;
    f32 _244;
    f32 _248;
    f32 _24C;
    u32 _250;
    u32 mAngerFrame;
    u32 _258;
    u32 _25C;
    u32 _260;
    u32 _264;
    u32 _268;
    f32 _26C;
    u32 _270;
};

}}}}  // namespace scn::step::boss::landia

#endif
