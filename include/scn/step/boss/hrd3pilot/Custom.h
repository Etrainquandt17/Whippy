#ifndef SCN_STEP_BOSS_HRD3PILOT_CUSTOM_H
#define SCN_STEP_BOSS_HRD3PILOT_CUSTOM_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/hrd3pilot/TailCtrl.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

class Custom;

}}}}  // namespace scn::step::boss::hrd3pilot

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::hrd3pilot::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

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
    virtual void onProcMove();
    virtual void onProcFixPos();
    virtual void onProcObjCollReact();

    void reqMotionMissileFar();
    void setNextStateMissile();
    hel::math::Vector3 getMissileLaunchPos();
    TailCtrl& tailCtrl();

private:
    TailCtrl mTailCtrl;
};

}}}}  // namespace scn::step::boss::hrd3pilot

#endif
