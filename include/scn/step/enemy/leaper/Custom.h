#ifndef SCN_STEP_ENEMY_LEAPER_CUSTOM_H
#define SCN_STEP_ENEMY_LEAPER_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace leaper {

// TODO: members and the other functions.
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    void setBodyColl();
    void reqShot(hel::math::Vector2 dir);

private:
    // TODO: members.
    u32 _8[18];
};

}}}}  // namespace scn::step::enemy::leaper

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::leaper::Custom>();

}}  // namespace hel::common

#endif
