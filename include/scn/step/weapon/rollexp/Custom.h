#ifndef SCN_STEP_WEAPON_ROLLEXP_CUSTOM_H
#define SCN_STEP_WEAPON_ROLLEXP_CUSTOM_H

#include "scn/step/ocoll/AttackType.h"
#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace rollexp {

class Custom;

}}}}  // namespace scn::step::weapon::rollexp

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::rollexp::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace rollexp {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void changeAttackType(ocoll::AttackType type);
    ocoll::AttackType getAttackType() const;
    void setAttackRadius(f32 radius);
    f32 getAttackRadius() const;
    void setAttackFrame(u32 frame);
    u32 getAttackFrame() const;

private:
    ocoll::AttackType mAttackType;
    f32 mAttackRadius;
    u32 mAttackFrame;
};

}}}}  // namespace scn::step::weapon::rollexp

#endif
