#ifndef SCN_STEP_BOSS_LANDIA_CUSTOM_H
#define SCN_STEP_BOSS_LANDIA_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class Custom;

}}}}  // namespace scn::step::boss::landia

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::landia::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace landia {

class SingleCtrl;
class SingleWeaponCtrl;
class CollisionCtrl;
class HeadAngleCtrl;
class HowlCtrl;
class SwitchModelCtrl;
class WaftCtrl;
class WindCtrl;

// TODO: members.
class Custom : public CustomBase {
public:
    Custom(Boss& boss);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    SingleCtrl& singleCtrl();
    SingleWeaponCtrl& singleWeaponCtrl();
    CollisionCtrl& collisionCtrl();
    HeadAngleCtrl& headAngleCtrl();
    HowlCtrl& howlCtrl();
    SwitchModelCtrl& switchModelCtrl();
    WaftCtrl& waftCtrl();
    WindCtrl& windCtrl();
    void setSubAnimEyeAngry();

private:
    // TODO: members.
    u32 _8[72];
};

}}}}  // namespace scn::step::boss::landia

#endif
