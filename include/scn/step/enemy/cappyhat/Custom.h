#ifndef SCN_STEP_ENEMY_CAPPYHAT_CUSTOM_H
#define SCN_STEP_ENEMY_CAPPYHAT_CUSTOM_H

#include "hel/geo/Rect.h"
#include "scn/step/enemy/CustomBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappyhat {

class Custom;

}}}}  // namespace scn::step::enemy::cappyhat

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::cappyhat::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace cappyhat {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual void onProcFixPos();

    bool chkCulling();
    hel::geo::Rect calcCullingRect();
};

}}}}  // namespace scn::step::enemy::cappyhat

#endif
