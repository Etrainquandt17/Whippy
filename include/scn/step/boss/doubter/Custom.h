#ifndef SCN_STEP_BOSS_DOUBTER_CUSTOM_H
#define SCN_STEP_BOSS_DOUBTER_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/CaptureCtrl.h"
#include "scn/step/boss/doubter/JugglingCtrl.h"
#include "scn/step/boss/doubter/PunchCtrl.h"
#include "scn/step/boss/doubter/WaftPositionCtrl.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class Custom;

}}}}  // namespace scn::step::boss::doubter

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::doubter::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace doubter {

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
    virtual void onProcFixPos();

    BodyCollCtrl& bodyCollCtrl();
    CaptureCtrl& captureCtrl();
    JugglingCtrl& jugglingCtrl();
    PunchCtrl& punchCtrlR();
    PunchCtrl& punchCtrlL();
    WaftPositionCtrl& waftPositionCtrl();

private:
    BodyCollCtrl mBodyCollCtrl;
    CaptureCtrl mCaptureCtrl;
    JugglingCtrl mJugglingCtrl;
    PunchCtrl mPunchCtrlR;
    PunchCtrl mPunchCtrlL;
    WaftPositionCtrl mWaftPositionCtrl;
};

}}}}  // namespace scn::step::boss::doubter

#endif
