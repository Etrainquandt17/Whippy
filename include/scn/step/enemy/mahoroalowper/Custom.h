#ifndef SCN_STEP_ENEMY_MAHOROALOWPER_CUSTOM_H
#define SCN_STEP_ENEMY_MAHOROALOWPER_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroalowper {

class Custom;

}}}}  // namespace scn::step::enemy::mahoroalowper

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::mahoroalowper::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace mahoroalowper {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onDamaged();
};

}}}}  // namespace scn::step::enemy::mahoroalowper

#endif
