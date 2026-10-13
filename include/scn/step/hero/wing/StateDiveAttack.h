#ifndef SCN_STEP_HERO_WING_STATEDIVEATTACK_H
#define SCN_STEP_HERO_WING_STATEDIVEATTACK_H

namespace scn {
namespace step {
namespace hero {

class Hero;

namespace wing {

class StateDiveAttack {
public:
    static bool TryToChangeState(Hero* hero);
};

}}}}  // namespace scn::step::hero::wing

#endif
