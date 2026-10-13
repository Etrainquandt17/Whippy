#ifndef SCN_STEP_ENEMY_TWISTER_CUSTOM_H
#define SCN_STEP_ENEMY_TWISTER_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace twister {

class Custom;

}}}}  // namespace scn::step::enemy::twister

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::twister::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace twister {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onVacuumReceive();
    virtual bool onDamaged();
    virtual void onCaptured();
    virtual void onDead();

    f32 getThetaX() const;
    void setThetaX(f32 theta);
    f32 getThetaY() const;
    void setThetaY(f32 theta);

private:
    f32 mThetaX;
    f32 mThetaY;
};

}}}}  // namespace scn::step::enemy::twister

#endif
