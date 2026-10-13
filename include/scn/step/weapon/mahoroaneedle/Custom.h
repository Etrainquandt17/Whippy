#ifndef SCN_STEP_WEAPON_MAHOROANEEDLE_CUSTOM_H
#define SCN_STEP_WEAPON_MAHOROANEEDLE_CUSTOM_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

class Custom;

}}}}  // namespace scn::step::weapon::mahoroaneedle

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::mahoroaneedle::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void reqChangeStateStart();
    void updateRot(f32 rot);
    hel::math::Vector3 getUpDir() const;

private:
    hel::math::Vector3 mUpDir;
    f32 mRot;
};

}}}}  // namespace scn::step::weapon::mahoroaneedle

#endif
