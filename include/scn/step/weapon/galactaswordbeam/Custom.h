#ifndef SCN_STEP_WEAPON_GALACTASWORDBEAM_CUSTOM_H
#define SCN_STEP_WEAPON_GALACTASWORDBEAM_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactaswordbeam {

class Custom;

}}}}  // namespace scn::step::weapon::galactaswordbeam

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::galactaswordbeam::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace galactaswordbeam {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void setIsReqStarEffect(bool isReq);
    bool isReqStarEffect() const;

private:
    bool mIsReqStarEffect;
};

}}}}  // namespace scn::step::weapon::galactaswordbeam

#endif
