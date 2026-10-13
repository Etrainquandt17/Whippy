#ifndef SCN_STEP_HERO_FIGHTER_FIGHTER_H
#define SCN_STEP_HERO_FIGHTER_FIGHTER_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace fighter {

class Fighter : public AbilityBase {
public:
    Fighter(Component& component, Hero& hero);
    virtual ~Fighter();

private:
    u32 _C;
};

}}}}  // namespace scn::step::hero::fighter

#endif
