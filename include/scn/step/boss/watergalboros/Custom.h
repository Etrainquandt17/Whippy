#ifndef SCN_STEP_BOSS_WATERGALBOROS_CUSTOM_H
#define SCN_STEP_BOSS_WATERGALBOROS_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/watergalboros/CaptureCtrl.h"
#include "scn/step/boss/watergalboros/WeaponCtrl.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

class Custom;

}}}}  // namespace scn::step::boss::watergalboros

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::watergalboros::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

class Custom : public CustomBase {
public:
    Custom(Boss& boss);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual void onInit();
    virtual void onAppear();
    virtual void onStart();
    virtual void onDamage();
    virtual void onDead();
    virtual void onProcAnim();
    virtual void onProcFixPos();

    WeaponCtrl& weaponCtrl();
    CaptureCtrl& captureCtrl();

private:
    WeaponCtrl mWeaponCtrl;
    CaptureCtrl mCaptureCtrl;
};

}}}}  // namespace scn::step::boss::watergalboros

#endif
