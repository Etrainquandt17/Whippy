#ifndef SCN_STEP_BOSS_GOLIATH_CUSTOM_H
#define SCN_STEP_BOSS_GOLIATH_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/goliath/CameraCtrl.h"
#include "scn/step/boss/goliath/CollisionCtrl.h"
#include "scn/step/boss/goliath/ElevationCtrl.h"
#include "scn/step/boss/goliath/EnemyCtrl.h"
#include "scn/step/boss/goliath/EyeCtrl.h"
#include "scn/step/boss/goliath/HairCtrl.h"
#include "scn/step/boss/goliath/IcicleCtrl.h"
#include "scn/step/boss/goliath/LandCtrl.h"
#include "scn/step/boss/goliath/PunchCtrl.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class Custom;

}}}}  // namespace scn::step::boss::goliath

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::goliath::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class Custom : public CustomBase {
public:
    Custom(Boss& boss);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual void onInit();
    virtual void onAppear();
    virtual void onStart();
    virtual void onDamage();
    virtual void onDead();
    virtual void onStateChange();
    virtual void onProcAnim();
    virtual void onProcMove();
    virtual void onProcFixPos();

    CollisionCtrl& collisionCtrl();
    ElevationCtrl& elevationCtrl();
    EnemyCtrl& enemyCtrl();
    IcicleCtrl& icicleCtrl();
    HairCtrl& hairCtrl();
    EyeCtrl& eyeCtrl();
    LandCtrl& landCtrl();
    CameraCtrl& cameraCtrl();
    PunchCtrl& punchCtrl();

private:
    CollisionCtrl mCollisionCtrl;
    ElevationCtrl mElevationCtrl;
    EnemyCtrl mEnemyCtrl;
    IcicleCtrl mIcicleCtrl;
    HairCtrl mHairCtrl;
    EyeCtrl mEyeCtrl;
    LandCtrl mLandCtrl;
    CameraCtrl mCameraCtrl;
    PunchCtrl mPunchCtrl;
};

}}}}  // namespace scn::step::boss::goliath

#endif
