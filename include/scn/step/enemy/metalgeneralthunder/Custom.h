#ifndef SCN_STEP_ENEMY_METALGENERALTHUNDER_CUSTOM_H
#define SCN_STEP_ENEMY_METALGENERALTHUNDER_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralthunder {

class Custom;

}}}}  // namespace scn::step::enemy::metalgeneralthunder

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::metalgeneralthunder::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralthunder {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onDamaged();
    virtual bool reqCustomDeadEffect();
};

}}}}  // namespace scn::step::enemy::metalgeneralthunder

#endif
