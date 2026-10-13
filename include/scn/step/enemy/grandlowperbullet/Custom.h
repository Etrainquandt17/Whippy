#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_CUSTOM_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_CUSTOM_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/CustomBase.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

}
namespace enemy {
namespace grandlowperbullet {

class Custom;

}}}}  // namespace scn::step::enemy::grandlowperbullet

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::grandlowperbullet::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onDamaged();
    virtual bool reqCustomDeadEffect();

    void setTargetPos(const hel::math::Vector3& pos);
    hel::math::Vector3 getTargetPos() const;
    void setTargetHero(util::ObjRefHandle<hero::Hero> hero);
    util::ObjRefHandle<hero::Hero> getTargetHero() const;
    void reqImageEffect();

private:
    hel::math::Vector3 mTargetPos;
    util::ObjRefHandle<hero::Hero> mTargetHero;
};

}}}}  // namespace scn::step::enemy::grandlowperbullet

#endif
