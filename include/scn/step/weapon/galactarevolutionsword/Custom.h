#ifndef SCN_STEP_WEAPON_GALACTAREVOLUTIONSWORD_CUSTOM_H
#define SCN_STEP_WEAPON_GALACTAREVOLUTIONSWORD_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactarevolutionsword {

class Custom;

}}}}  // namespace scn::step::weapon::galactarevolutionsword

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::galactarevolutionsword::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace galactarevolutionsword {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void setFloorPosY(f32 y);
    f32 getFloorPosY() const;

private:
    f32 mFloorPosY;
};

}}}}  // namespace scn::step::weapon::galactarevolutionsword

#endif
