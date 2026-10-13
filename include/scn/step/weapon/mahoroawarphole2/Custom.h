#ifndef SCN_STEP_WEAPON_MAHOROAWARPHOLE2_CUSTOM_H
#define SCN_STEP_WEAPON_MAHOROAWARPHOLE2_CUSTOM_H

#include "hel/common/RuntimeTypeInfo.h"
#include "hel/math/Vector3.h"
#include "scn/step/weapon/CustomBase.h"
#include "scn/step/weapon/Weapon.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarphole2 {

class Custom;

}}}}  // namespace scn::step::weapon::mahoroawarphole2

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::mahoroawarphole2::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarphole2 {

// TODO: the unit is not written yet; the members are read from its constructor and the functions from the map.
class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void reqFlash();
    void reqBlackFlash();
    void setScale(f32 scale);
    void updateFlash();
    f32 getFlashAlpha() const;
    hel::math::Vector3 getTargetFront() const;
    bool isBlackFlashRequested() const;
    void reqChangeStateEnd();
    bool isEnd() const;

private:
    bool _8;
    hel::math::Vector3 _C;
    bool _18;
    bool _19;
};

}}}}  // namespace scn::step::weapon::mahoroawarphole2

#endif
