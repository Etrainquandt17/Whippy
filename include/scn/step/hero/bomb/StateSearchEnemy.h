#ifndef SCN_STEP_HERO_BOMB_STATESEARCHENEMY_H
#define SCN_STEP_HERO_BOMB_STATESEARCHENEMY_H

namespace scn {
namespace step {
namespace hero {
class Hero;
}}}  // namespace scn::step::hero

namespace scn {
namespace step {
namespace hero {
namespace bomb {

class GearBombController;

class StateSearchEnemy {
public:
    static bool TryToChangeState(Hero* hero, GearBombController& controller);
};

}}}}  // namespace scn::step::hero::bomb

#endif
