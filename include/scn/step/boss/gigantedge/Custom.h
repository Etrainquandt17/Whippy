#ifndef SCN_STEP_BOSS_GIGANTEDGE_CUSTOM_H
#define SCN_STEP_BOSS_GIGANTEDGE_CUSTOM_H

#include "scn/step/boss/CustomBase.h"

namespace scn {
namespace step {
namespace boss {
namespace gigantedge {

class Custom;

}}}}  // namespace scn::step::boss::gigantedge

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::gigantedge::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace gigantedge {

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

    void setBodyCollGuard();
    void reqSwordShot(bool isTriple);
};

}}}}  // namespace scn::step::boss::gigantedge

#endif
