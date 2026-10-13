#ifndef SCN_STEP_BOSS_MOUNDEATH_CUSTOM_H
#define SCN_STEP_BOSS_MOUNDEATH_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class Custom;

}}}}  // namespace scn::step::boss::moundeath

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::moundeath::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

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

    void setBodyCollDefault();
    void setBodyCollRolling();
};

}}}}  // namespace scn::step::boss::moundeath

#endif
