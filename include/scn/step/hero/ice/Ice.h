#ifndef SCN_STEP_HERO_ICE_ICE_H
#define SCN_STEP_HERO_ICE_ICE_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace ice {

class Ice : public AbilityBase {
public:
    Ice(Component& component, Hero& hero);
    virtual ~Ice();

private:
    u32 _C;
};

}}}}  // namespace scn::step::hero::ice

#endif
