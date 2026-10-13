#ifndef SCN_STEP_ENEMY_WAPOD_CUSTOM_H
#define SCN_STEP_ENEMY_WAPOD_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

class Custom;

}}}}  // namespace scn::step::enemy::wapod

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::wapod::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onVacuumReceive();
    virtual bool onDamaged();
    virtual void onDead();

    void setWapodpodUid(u64 uid);
    u32 wapodpodVariation() const;
    f32 initPosY() const;
    void turn();
    void landHitDead();
    void fixPosInValid();

private:
    u64 mWapodpodUid;
    u32 mWapodpodVariation;
    bool mIsVacuum;
    f32 mInitPosY;
    u32 mTurnFrame;
};

}}}}  // namespace scn::step::enemy::wapod

#endif
