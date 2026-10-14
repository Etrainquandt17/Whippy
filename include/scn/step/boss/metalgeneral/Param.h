#ifndef SCN_STEP_BOSS_METALGENERAL_PARAM_H
#define SCN_STEP_BOSS_METALGENERAL_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "hel/math/Vec3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

struct CollParam {
    f32 mBodyRadius;
    hel::math::Vec2 mBodyOffset;
    hel::math::Vec2 mBodyOffsetEnd;
    f32 mAttackRadius;
    hel::math::Vec2 mAttackOffset;
    hel::math::Vec2 mAttackOffsetEnd;
};

// TODO: only the members that the written states read are named; the types of the others follow how they are loaded.
struct Param {
    u32 _0[7];
    gobj::MoveParamDecel _1C;
    gobj::MoveParamDecel _20;
    gobj::MoveParamFall _24;
    f32 _30;
    f32 mHitDepth;
    CollParam mColl;
    CollParam mCollPatriot;
    f32 _88;
    f32 _8C;
    f32 _90;
    f32 _94;
    f32 _98;
    f32 _9C;
    f32 _A0;
    f32 _A4;
    f32 _A8;
    f32 _AC;
    gobj::MoveParamAccel _B0;
    gobj::MoveParamAccel _BC;
    gobj::MoveParamAccel _C8;
    f32 _D4;
    f32 _D8;
    gobj::MoveParamDecel _DC;
    gobj::MoveParamFall _E0;
    f32 _EC;
    f32 _F0;
    f32 _F4;
    hel::math::Vec2 _F8;
    hel::math::Vec2 _100;
    f32 _108;
    u32 _10C;
    gobj::MoveParamAccel _110;
    f32 _11C;
    f32 _120;
    f32 _124;
    f32 _128;
    f32 _12C;
    u32 _130;
    f32 _134;
    f32 _138;
    u32 _13C;
    u32 _140;
    f32 _144;
    u32 _148;
    u32 _14C;
    f32 _150;
    f32 _154;
    gobj::MoveParamAccel _158;
    u32 _164;
    f32 _168;
    f32 _16C;
    f32 _170;
    u32 _174;
    f32 _178;
    f32 _17C;
    f32 _180;
    f32 _184;
    f32 _188;
    f32 _18C;
    f32 _190;
    f32 _194;
    f32 _198;
    f32 _19C;
    f32 _1A0;
    f32 _1A4;
    f32 _1A8;
    f32 _1AC;
    hel::math::Vec2 _1B0;
    u32 _1B8;
    f32 _1BC;
    f32 _1C0;
    f32 _1C4;
    f32 _1C8;
    u32 _1CC;
    u32 _1D0;
    f32 _1D4;
    f32 _1D8;
    f32 _1DC;
    f32 _1E0;
    f32 _1E4;
    f32 _1E8;
    u32 _1EC;
    f32 _1F0;
    f32 _1F4;
    f32 _1F8;
    f32 _1FC;
    u32 _200;
    gobj::MoveParamAccel _204;
    u32 _210;
    u32 _214;
    f32 _218;
    u32 _21C;
    u32 _220;
    f32 _224;
    f32 _228;
    f32 _22C;
    f32 _230;
    f32 _234;
    u32 _238;
    u32 _23C;
    u32 _240;
    f32 _244;
    u32 _248;
    u32 _24C;
    f32 _250;
    f32 _254;
    u32 _258;
    f32 _25C;
    f32 _260;
    f32 _264;
    f32 _268;
    u32 _26C;
    u32 _270;
    u32 _274;
    f32 _278;
    hel::math::Vec3 _27C;
    f32 _288;
    u32 _28C;
    u32 _290;
    f32 _294;
    f32 _298;
    f32 _29C;
    f32 _2A0;
    f32 _2A4;
    u32 _2A8;
    f32 _2AC;
    f32 _2B0;
    hel::math::Vec3 _2B4;
    hel::math::Vec3 _2C0;
    u32 _2CC;
    u32 _2D0;
    u32 _2D4;
    u32 _2D8;
    u32 _2DC;
    f32 _2E0;
    f32 _2E4;
    hel::math::Vec3 _2E8;
    f32 mDamageInfoDigitWidth;
#ifdef VERSION_SUKK01
    f32 mDamageInfoSpaceWidth;
    f32 mDamageInfoCommaWidth;
#endif
    f32 mDamageInfoRandX;
    f32 mDamageInfoRandY;
    f32 mDamageInfoRandScale;
    int mDamageInfoRandNumber;
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
