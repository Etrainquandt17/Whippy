#ifndef SCN_STEP_HERO_WATER_WATER_H
#define SCN_STEP_HERO_WATER_WATER_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace water {

class Water : public AbilityBase {
public:
    Water(Component& component, Hero& hero);
    virtual ~Water();

private:
    u32 _C[(0x1C - 0xC) / 4];
};

}}}}  // namespace scn::step::hero::water

#endif
