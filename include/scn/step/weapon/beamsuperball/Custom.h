#ifndef SCN_STEP_WEAPON_BEAMSUPERBALL_CUSTOM_H
#define SCN_STEP_WEAPON_BEAMSUPERBALL_CUSTOM_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace beamsuperball {

class Custom;

}}}}  // namespace scn::step::weapon::beamsuperball

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::beamsuperball::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace beamsuperball {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void setMoveCenter(const hel::math::Vector3& center);
    bool isSetMoveCenter() const;
    hel::math::Vector3 getMoveCenter() const;

private:
    bool mIsSetMoveCenter;
    hel::math::Vector3 mMoveCenter;
};

}}}}  // namespace scn::step::weapon::beamsuperball

#endif
