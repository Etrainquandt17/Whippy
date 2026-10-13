#ifndef SCN_STEP_WEAPON_MAHOROASUPERFIRE_CUSTOM_H
#define SCN_STEP_WEAPON_MAHOROASUPERFIRE_CUSTOM_H

#include "hel/geo/Rect.h"
#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroasuperfire {

class Custom;

}}}}  // namespace scn::step::weapon::mahoroasuperfire

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::mahoroasuperfire::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace mahoroasuperfire {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void setMoveLimitRect(const hel::geo::Rect& rect);
    bool isMoveLimitRectValid() const;
    hel::geo::Rect getMoveLimitRect() const;

private:
    bool mIsMoveLimitRectValid;
    hel::geo::Rect mMoveLimitRect;
};

}}}}  // namespace scn::step::weapon::mahoroasuperfire

#endif
