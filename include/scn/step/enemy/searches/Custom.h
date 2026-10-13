#ifndef SCN_STEP_ENEMY_SEARCHES_CUSTOM_H
#define SCN_STEP_ENEMY_SEARCHES_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace searches {

class Custom;

}}}}  // namespace scn::step::enemy::searches

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::searches::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace searches {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onHitPointIsZero();
    virtual bool onDamaged();

    bool isPlayerInArea();
    bool searchesDamage();
};

}}}}  // namespace scn::step::enemy::searches

#endif
