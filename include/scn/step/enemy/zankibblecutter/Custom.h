#ifndef SCN_STEP_ENEMY_ZANKIBBLECUTTER_CUSTOM_H
#define SCN_STEP_ENEMY_ZANKIBBLECUTTER_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace zankibblecutter {

class Custom;

}}}}  // namespace scn::step::enemy::zankibblecutter

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::zankibblecutter::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace zankibblecutter {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onVacuumReceive();
    virtual bool reqCustomDeadEffect();
};

}}}}  // namespace scn::step::enemy::zankibblecutter

#endif
