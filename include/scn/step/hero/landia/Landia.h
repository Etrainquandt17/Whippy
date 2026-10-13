#ifndef SCN_STEP_HERO_LANDIA_LANDIA_H
#define SCN_STEP_HERO_LANDIA_LANDIA_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace landia {

class Landia : public AbilityBase {
public:
    Landia(Component& component, Hero& hero);
    virtual ~Landia();

private:
    u32 _C[(0x18 - 0xC) / 4];
};

}}}}  // namespace scn::step::hero::landia

#endif
