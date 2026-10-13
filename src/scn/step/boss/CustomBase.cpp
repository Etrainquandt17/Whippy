#include "scn/step/boss/CustomBase.h"

#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/common/StateWait.h"

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::CustomBase>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::boss::ICustom>(), RuntimeTypeInfo::NoName());
    return ti;
}

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {

CustomBase::CustomBase(Boss& boss) : mBoss(boss) {}

void CustomBase::onInit() {
    Boss* boss = &mBoss;
    boss->stateChanger().setNextState<common::StateWait, Boss*>(boss);
}

void CustomBase::onAppear() {}

void CustomBase::onStart() {}

void CustomBase::onDamage() {}

void CustomBase::onDead() {}

void CustomBase::onStateChange() {}

void CustomBase::onScriptRequested() {}

void CustomBase::onHitStopStart() {}

void CustomBase::onHitStopEnd() {}

void CustomBase::onObjStopStarted() {}

void CustomBase::onObjStopFinished() {}

void CustomBase::onProcAnim() {}

void CustomBase::onProcMove() {}

void CustomBase::onProcFixPos() {}

void CustomBase::onProcObjCollReact() {}

void CustomBase::onUpdateUseGPU() {}

hel::math::Vector2 CustomBase::getFirstOffs() const {
    return hel::math::Vector2(0.0f, 0.0f);
}

const hel::common::RuntimeTypeInfo& CustomBase::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<CustomBase>();
}

}}}  // namespace scn::step::boss
