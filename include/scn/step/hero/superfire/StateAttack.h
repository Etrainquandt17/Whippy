#ifndef SCN_STEP_HERO_SUPERFIRE_STATEATTACK_H
#define SCN_STEP_HERO_SUPERFIRE_STATEATTACK_H

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace superfire {

class StateAttack {
public:
    static bool TryToChangeState(Hero* hero);
};

}}}}  // namespace scn::step::hero::superfire

#endif
