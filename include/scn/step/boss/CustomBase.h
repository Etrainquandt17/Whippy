#ifndef SCN_STEP_BOSS_CUSTOMBASE_H
#define SCN_STEP_BOSS_CUSTOMBASE_H

#include "hel/common/NonCopyable.h"
#include "scn/step/boss/ICustom.h"

namespace scn {
namespace step {
namespace boss {

class Boss;
class CustomBase;

}}}  // namespace scn::step::boss

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::CustomBase>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {

class CustomBase : public ICustom, private hel::common::NonCopyable {
public:
    CustomBase(Boss& boss);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual void onInit();
    virtual void onAppear();
    virtual void onStart();
    virtual void onDamage();
    virtual void onDead();
    virtual void onStateChange();
    virtual void onScriptRequested();
    virtual void onHitStopStart();
    virtual void onHitStopEnd();
    virtual void onObjStopStarted();
    virtual void onObjStopFinished();
    virtual void onProcAnim();
    virtual void onProcMove();
    virtual void onProcFixPos();
    virtual void onProcObjCollReact();
    virtual void onUpdateUseGPU();
    virtual hel::math::Vector2 getFirstOffs() const;

    Boss& obj() const;
    Boss& obj();
    Boss* objPtr();

protected:
    Boss& mBoss;
};

}}}  // namespace scn::step::boss

#endif
