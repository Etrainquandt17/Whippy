#ifndef SCN_STEP_WEAPON_MAHOROABLACKHOLE_CUSTOM_H
#define SCN_STEP_WEAPON_MAHOROABLACKHOLE_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroablackhole {

class Custom;

}}}}  // namespace scn::step::weapon::mahoroablackhole

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::mahoroablackhole::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace mahoroablackhole {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void reqChangeStateToEnd();
    bool isRequestedChangeStateToEnd() const;

private:
    bool mIsRequestedChangeStateToEnd;
};

}}}}  // namespace scn::step::weapon::mahoroablackhole

#endif
