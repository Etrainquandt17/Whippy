#ifndef SCN_STEP_HERO_SPARK_CUSTOM_H
#define SCN_STEP_HERO_SPARK_CUSTOM_H

#include "scn/step/hero/AbilityCustomBase.h"
#include "scn/step/hero/ShakeCharge.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace spark {
class Custom;
}}}}  // namespace scn::step::hero::spark

namespace hel {
namespace common {
// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::hero::spark::Custom>();
}}  // namespace hel::common

namespace scn {
namespace step {
namespace hero {
namespace spark {

class Custom : public AbilityCustomBase {
public:
    Custom(Hero& hero);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    ShakeCharge& shakeCharge();
    bool isAction() const;
    void setAction(bool isAction);

private:
    ShakeCharge mShakeCharge;
    bool mIsAction;
};

}}}}  // namespace scn::step::hero::spark

#endif
