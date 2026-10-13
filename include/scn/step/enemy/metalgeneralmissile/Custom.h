#ifndef SCN_STEP_ENEMY_METALGENERALMISSILE_CUSTOM_H
#define SCN_STEP_ENEMY_METALGENERALMISSILE_CUSTOM_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralmissile {

class Custom;

}}}}  // namespace scn::step::enemy::metalgeneralmissile

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::metalgeneralmissile::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralmissile {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy, bool _1);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onDamaged();
    virtual bool reqCustomDeadEffect();

    void reqRollExp();
    void setFallInitPos(const hel::math::Vector3& pos);
    const hel::math::Vector3& getFallInitPos() const;
    void setIsExpSED3(bool isExpSED3);

private:
    hel::math::Vector3 mFallInitPos;
    bool _14;
    bool mIsExpSED3;
};

}}}}  // namespace scn::step::enemy::metalgeneralmissile

#endif
