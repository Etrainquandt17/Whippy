#ifndef SCN_STEP_ENEMY_BONKERSBOMB_PARAMDATA_H
#define SCN_STEP_ENEMY_BONKERSBOMB_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace bonkersbomb {

// TODO: the names are guesses: nothing in the game names what Param::bonkersbomb() returns.
struct ParamData {
    struct Shape {
        f32 mWidth;
        f32 mHeight;
        f32 mSlant;
    };

    struct Shot {
        gobj::MoveParamFall mFall;
        f32 mRotSpeed;
    };

    struct Landing {
        u32 mFrame;
        f32 mSpeedH;
        gobj::MoveParamDecel mDecel;
        f32 mRotSpeed;
        f32 mRotDecel;
    };

    Shape mShape;
    Shape mShapeBig;
    Shot mShot;
    Shot mShotBig;
    Landing mLanding;
    Landing mLandingBig;
};

}}}}  // namespace scn::step::enemy::bonkersbomb

#endif
