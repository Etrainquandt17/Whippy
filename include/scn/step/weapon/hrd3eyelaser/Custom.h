#ifndef SCN_STEP_WEAPON_HRD3EYELASER_CUSTOM_H
#define SCN_STEP_WEAPON_HRD3EYELASER_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace hrd3eyelaser {

class Custom;

}}}}  // namespace scn::step::weapon::hrd3eyelaser

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::hrd3eyelaser::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace hrd3eyelaser {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void setLengthMax(f32 length);
    f32 getLengthMax() const;

private:
    f32 mLengthMax;
};

}}}}  // namespace scn::step::weapon::hrd3eyelaser

#endif
