#ifndef SCN_STEP_ENEMY_CHILLY_CUSTOM_H
#define SCN_STEP_ENEMY_CHILLY_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace chilly {

class Custom;

}}}}  // namespace scn::step::enemy::chilly

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::chilly::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace chilly {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual void setupSuperEnemyEffect();
};

}}}}  // namespace scn::step::enemy::chilly

#endif
