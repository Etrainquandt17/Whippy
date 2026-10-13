#ifndef SCN_STEP_ENEMY_METALGENERALBIT_CUSTOM_H
#define SCN_STEP_ENEMY_METALGENERALBIT_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

class Custom;

}}}}  // namespace scn::step::enemy::metalgeneralbit

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::metalgeneralbit::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual void onProcFixPos();

    void reqRollExp();

private:
    u32 _8;
    f32 _c;
};

}}}}  // namespace scn::step::enemy::metalgeneralbit

#endif
