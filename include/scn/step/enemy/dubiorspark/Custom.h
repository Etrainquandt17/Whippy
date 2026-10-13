#ifndef SCN_STEP_ENEMY_DUBIORSPARK_CUSTOM_H
#define SCN_STEP_ENEMY_DUBIORSPARK_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace dubiorspark {

class Custom;

}}}}  // namespace scn::step::enemy::dubiorspark

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::dubiorspark::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace dubiorspark {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onDamaged();
    virtual bool reqCustomDeadEffect();
};

}}}}  // namespace scn::step::enemy::dubiorspark

#endif
