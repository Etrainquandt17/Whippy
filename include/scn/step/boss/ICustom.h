#ifndef SCN_STEP_BOSS_ICUSTOM_H
#define SCN_STEP_BOSS_ICUSTOM_H

#include "hel/common/RuntimeTypeInfo.h"
#include "hel/math/Vector2.h"

namespace scn {
namespace step {
namespace boss {

class ICustom {
public:
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~ICustom();
    virtual void onInit() = 0;
    virtual void onAppear() = 0;
    virtual void onStart() = 0;
    virtual void onDamage() = 0;
    virtual void onDead() = 0;
    virtual void onStateChange() = 0;
    virtual void onScriptRequested() = 0;
    virtual void onHitStopStart() = 0;
    virtual void onHitStopEnd() = 0;
    virtual void onObjStopStarted() = 0;
    virtual void onObjStopFinished() = 0;
    virtual void onProcAnim() = 0;
    virtual void onProcMove() = 0;
    virtual void onProcFixPos() = 0;
    virtual void onProcObjCollReact() = 0;
    virtual void onUpdateUseGPU() = 0;
    virtual hel::math::Vector2 getFirstOffs() const = 0;
};

}}}  // namespace scn::step::boss

#endif
