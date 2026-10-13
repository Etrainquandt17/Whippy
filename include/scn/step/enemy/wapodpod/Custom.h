#ifndef SCN_STEP_ENEMY_WAPODPOD_CUSTOM_H
#define SCN_STEP_ENEMY_WAPODPOD_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace wapodpod {

class Custom;

}}}}  // namespace scn::step::enemy::wapodpod

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::wapodpod::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace wapodpod {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onVacuumReceive();
    virtual bool onDamaged();
    virtual bool onInWater();
    virtual void onCaptured();
    virtual void onDead();
    virtual void onProcFixPos();
    virtual bool reqCustomDeadEffect();

    void requestWapod();
    bool isExist() const;
    void setIsExist(bool isExist);
    bool isFixPos() const;
    void setIsFixPos(bool isFixPos);
    void setIsWait(bool isWait);
    void fixWapodPos();

private:
    util::ObjRefHandle<Enemy> mWapod;
    bool mIsExist;
    bool mIsWait;
    bool mIsCaptured;
    bool mIsFixPos;
    u32 mWaitFrame;
    f32 mRise;
};

}}}}  // namespace scn::step::enemy::wapodpod

#endif
