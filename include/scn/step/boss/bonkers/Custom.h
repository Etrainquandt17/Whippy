#ifndef SCN_STEP_BOSS_BONKERS_CUSTOM_H
#define SCN_STEP_BOSS_BONKERS_CUSTOM_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/CustomBase.h"
#include "scn/step/map/BinEnemySize.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

class Custom;

}}}}  // namespace scn::step::boss::bonkers

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::bonkers::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

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
    void setBodyCollSwing();
    void reqBomb(hel::math::Vector2 pos, hel::math::Vector2 speed, map::BinEnemySize size);
};

}}}}  // namespace scn::step::boss::bonkers

#endif
