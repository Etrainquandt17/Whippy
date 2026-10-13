#ifndef SCN_STEP_ENEMY_CUSTOMBASE_H
#define SCN_STEP_ENEMY_CUSTOMBASE_H

#include "hel/common/NonCopyable.h"
#include "scn/step/enemy/ICustom.h"

namespace scn {
namespace step {
namespace enemy {

class CustomBase;
class Enemy;

}}}  // namespace scn::step::enemy

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::CustomBase>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {

class CustomBase : public ICustom, private hel::common::NonCopyable {
public:
    CustomBase(Enemy& enemy);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onVacuumReceive();
    virtual bool onVacuumResist();
    virtual bool onDamaged();
    virtual bool onInWater();
    virtual bool onOutWater();
    virtual bool onRecover();
    virtual void onCaptured();
    virtual void onDead();
    virtual void onProcFixPos();
    virtual bool reqCustomDeadEffect();
    virtual void setupSuperEnemyEffect();

    Enemy& obj() const;
    Enemy& obj();

private:
    Enemy& mObj;
};

}}}  // namespace scn::step::enemy

#endif
