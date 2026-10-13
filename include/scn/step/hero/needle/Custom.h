#ifndef SCN_STEP_HERO_NEEDLE_CUSTOM_H
#define SCN_STEP_HERO_NEEDLE_CUSTOM_H

#include "scn/step/hero/AbilityCustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

class Custom : public AbilityCustomBase {
public:
    Custom(Hero& hero);
    virtual ~Custom();

    void shotAllWeapon(u32 num);

private:
    u32 _8[(0xB0 - 0x8) / 4];
};

}}}}  // namespace scn::step::hero::needle

#endif
