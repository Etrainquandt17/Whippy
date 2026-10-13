#ifndef SCN_STEP_ENEMY_SQUISHY_CUSTOM_H
#define SCN_STEP_ENEMY_SQUISHY_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

class Custom;

}}}}  // namespace scn::step::enemy::squishy

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::squishy::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onInWater();
    virtual bool onOutWater();

    bool isJumpFromWater();
    void setJumpFromWater(bool flag);
    bool isInWater(bool flag);

private:
    bool _8;
    bool _9;
    bool mIsJumpFromWater;
};

}}}}  // namespace scn::step::enemy::squishy

#endif
