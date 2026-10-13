#ifndef SCN_STEP_HERO_MIKE_UTILITY_HAT_H
#define SCN_STEP_HERO_MIKE_UTILITY_HAT_H

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace mike {
namespace utility {

class Hat {
public:
    static void Set(Hero& hero);
    static void Clear(Hero& hero);
    static void Wait(Hero& hero);
};

}}}}}  // namespace scn::step::hero::mike::utility

#endif
