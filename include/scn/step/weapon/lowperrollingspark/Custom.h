#ifndef SCN_STEP_WEAPON_LOWPERROLLINGSPARK_CUSTOM_H
#define SCN_STEP_WEAPON_LOWPERROLLINGSPARK_CUSTOM_H

#include "hel/math/Vector2.h"
#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace lowperrollingspark {

class Custom;

}}}}  // namespace scn::step::weapon::lowperrollingspark

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::lowperrollingspark::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace lowperrollingspark {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void setTotalFrame(u32 frame);
    u32 getTotalFrame() const;
    void setDelayFrame(u32 frame);
    u32 getDelayFrame() const;
    void setRotAngle(f32 angle);
    f32 getRotAngle() const;
    void setCenterPos(const hel::math::Vector2& pos);
    const hel::math::Vector2& getCenterPos() const;

private:
    u32 mTotalFrame;
    u32 mDelayFrame;
    f32 mRotAngle;
    hel::math::Vector2 mCenterPos;
};

}}}}  // namespace scn::step::weapon::lowperrollingspark

#endif
