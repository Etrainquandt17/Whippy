#ifndef SCN_STEP_HERO_NINJA_NINJA_H
#define SCN_STEP_HERO_NINJA_NINJA_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace ninja {

class Ninja : public AbilityBase {
public:
    Ninja(Component& component, Hero& hero);
    virtual ~Ninja();

private:
    u32 _C[(0x1C - 0xC) / 4];
};

}}}}  // namespace scn::step::hero::ninja

#endif
