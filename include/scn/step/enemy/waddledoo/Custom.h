#ifndef SCN_STEP_ENEMY_WADDLEDOO_CUSTOM_H
#define SCN_STEP_ENEMY_WADDLEDOO_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

class Custom;

}}}}  // namespace scn::step::enemy::waddledoo

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::waddledoo::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual void setupSuperEnemyEffect();
};

}}}}  // namespace scn::step::enemy::waddledoo

#endif
