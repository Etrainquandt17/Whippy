#ifndef SCN_STEP_WEAPON_STARSHOTLV1_CUSTOM_H
#define SCN_STEP_WEAPON_STARSHOTLV1_CUSTOM_H

#include "hel/common/MutableArray.h"
#include "scn/step/weapon/CustomBase.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {

namespace hero {
class Hero;
}

namespace weapon {
namespace starshotlv1 {

class Custom;

}}}}  // namespace scn::step::weapon::starshotlv1

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::starshotlv1::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace starshotlv1 {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void addHero(util::ObjRefHandle<hero::Hero> hero);
    void removeHero(util::ObjRefHandle<hero::Hero> hero);
    bool isHeroDisappeared();
    void cleanupHero();

private:
    hel::common::MutableArray<util::ObjRefHandle<hero::Hero>, 3> mHeroes;
    bool mIsHeroAdded;
};

}}}}  // namespace scn::step::weapon::starshotlv1

#endif
