#ifndef SCN_STEP_HERO_CRASH_UTILITY_H
#define SCN_STEP_HERO_CRASH_UTILITY_H

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace crash {

class Utility {
public:
    static void RequestHatEffectNormal(Hero& hero);
    static void RequestHatEffectAttack(Hero& hero);
};

}}}}  // namespace scn::step::hero::crash

#endif
