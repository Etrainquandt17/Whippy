#ifndef SCN_STEP_ENEMY_GOLIATHICICLE_CUSTOM_H
#define SCN_STEP_ENEMY_GOLIATHICICLE_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathicicle {

class Custom;

}}}}  // namespace scn::step::enemy::goliathicicle

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::goliathicicle::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace goliathicicle {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool reqCustomDeadEffect();
};

}}}}  // namespace scn::step::enemy::goliathicicle

#endif
