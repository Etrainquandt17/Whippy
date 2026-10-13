#ifndef SCN_STEP_HERO_MIKE_UTILITY_MIKE_H
#define SCN_STEP_HERO_MIKE_UTILITY_MIKE_H

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace mike {
namespace utility {

class Mike {
public:
    static void Set(Hero& hero);
    static void Clear(Hero& hero);
};

}}}}}  // namespace scn::step::hero::mike::utility

#endif
