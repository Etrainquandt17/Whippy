#ifndef SCN_STEP_BOSS_ROAH_CUSTOM_H
#define SCN_STEP_BOSS_ROAH_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/roah/CollisionCtrl.h"
#include "scn/step/boss/roah/MahoroaCtrl.h"
#include "scn/step/boss/roah/RotCtrl.h"
#include "scn/step/boss/roah/StormCtrl.h"
#include "scn/step/boss/roah/WeaponCtrl.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class Custom;

}}}}  // namespace scn::step::boss::roah

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::roah::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace roah {

class Custom : public CustomBase {
public:
    Custom(Boss& boss);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual void onInit();
    virtual void onStart();
    virtual void onDamage();
    virtual void onDead();
    virtual void onProcAnim();
    virtual void onProcMove();
    virtual void onProcFixPos();

    CollisionCtrl& collisionCtrl();
    WeaponCtrl& weaponCtrl();
    RotCtrl& rotCtrl();
    MahoroaCtrl& mahoroaCtrl();
    StormCtrl& stormCtrl();
    void setSubAnimTexture();
    void setSubAnimOar();
    void resetSubAnimOar();

private:
    CollisionCtrl mCollisionCtrl;
    WeaponCtrl mWeaponCtrl;
    RotCtrl mRotCtrl;
    MahoroaCtrl mMahoroaCtrl;
    StormCtrl mStormCtrl;
};

}}}}  // namespace scn::step::boss::roah

#endif
