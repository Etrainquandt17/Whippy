#ifndef SCN_STEP_WEAPON_MAHOROASUPERBEAMBALL_CUSTOM_H
#define SCN_STEP_WEAPON_MAHOROASUPERBEAMBALL_CUSTOM_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroasuperbeamball {

class Custom;

}}}}  // namespace scn::step::weapon::mahoroasuperbeamball

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::mahoroasuperbeamball::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace mahoroasuperbeamball {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void reqStartGlide(const hel::math::Vector3& pos, u32 frame);
    hel::math::Vector3 getTargetPos() const;
    u32 getGlideTotalFrame() const;
    bool isRequestedStartGlide() const;

private:
    hel::math::Vector3 mTargetPos;
    u32 mGlideTotalFrame;
    bool mIsRequestedStartGlide;
};

}}}}  // namespace scn::step::weapon::mahoroasuperbeamball

#endif
