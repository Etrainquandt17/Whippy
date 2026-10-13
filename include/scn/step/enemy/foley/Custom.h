#ifndef SCN_STEP_ENEMY_FOLEY_CUSTOM_H
#define SCN_STEP_ENEMY_FOLEY_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace foley {

class Custom;

}}}}  // namespace scn::step::enemy::foley

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::foley::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace foley {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onVacuumReceive();
    virtual bool onDamaged();

    void requestRollExp();
    void setAttack(bool isAttack);

private:
    bool mIsAttack;
};

}}}}  // namespace scn::step::enemy::foley

#endif
