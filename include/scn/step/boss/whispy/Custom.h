#ifndef SCN_STEP_BOSS_WHISPY_CUSTOM_H
#define SCN_STEP_BOSS_WHISPY_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/whispy/CaptureCtrl.h"
#include "scn/step/boss/whispy/DamageEyeCtrl.h"
#include "scn/step/boss/whispy/EnemyCtrl.h"
#include "scn/step/boss/whispy/EnemyReqBuff.h"
#include "scn/step/boss/whispy/FaceRotCtrl.h"
#include "scn/step/boss/whispy/TSCtrl.h"
#include "scn/step/boss/whispy/WindCtrl.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class Custom;

}}}}  // namespace scn::step::boss::whispy

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::whispy::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class Custom : public CustomBase {
public:
    Custom(Boss& boss);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual void onInit();
    virtual void onAppear();
    virtual void onStart();
    virtual void onDamage();
    virtual void onDead();
    virtual void onScriptRequested();
    virtual void onProcAnim();
    virtual void onProcFixPos();

    CaptureCtrl& captureCtrl();
    DamageEyeCtrl& damageEyeCtrl();
    EnemyReqBuff& enemyReqBuff();
    EnemyCtrl& enemyCtrl();
    FaceRotCtrl& faceRotCtrl();
    TSCtrl& tsctrl();
    WindCtrl& windCtrl();

private:
    CaptureCtrl mCaptureCtrl;
    DamageEyeCtrl mDamageEyeCtrl;
    EnemyReqBuff mEnemyReqBuff;
    EnemyCtrl mEnemyCtrl;
    FaceRotCtrl mFaceRotCtrl;
    TSCtrl mTSCtrl;
    WindCtrl mWindCtrl;
};

}}}}  // namespace scn::step::boss::whispy

#endif
