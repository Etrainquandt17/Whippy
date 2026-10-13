#ifndef SCN_STEP_ENEMY_AQUAROCK_CUSTOM_H
#define SCN_STEP_ENEMY_AQUAROCK_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace aquarock {

class Custom;

}}}}  // namespace scn::step::enemy::aquarock

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::aquarock::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace aquarock {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInWater();

    f32 getRadius() const;
    f32 getSpeed() const;
    f32 getAngleSpeed() const;

private:
    f32 mRadius;
    f32 mCircumference;
    f32 mSpeed;
    f32 mAngleSpeed;
};

}}}}  // namespace scn::step::enemy::aquarock

#endif
