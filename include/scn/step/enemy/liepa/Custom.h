#ifndef SCN_STEP_ENEMY_LIEPA_CUSTOM_H
#define SCN_STEP_ENEMY_LIEPA_CUSTOM_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace liepa {

class Custom;

}}}}  // namespace scn::step::enemy::liepa

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::liepa::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace liepa {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onDamaged();
    virtual void onProcFixPos();
    virtual bool reqCustomDeadEffect();

    f32 cameraCenterPrevPosX();
    bool isExistHeroInAttackRange();
    hel::math::Vector2 getNearestHeroInAttackRange();
    void reqShot();
    void setSubAnimTexture();
    void setBodyColl();

private:
    f32 mCameraCenterPrevPosX;
};

}}}}  // namespace scn::step::enemy::liepa

#endif
