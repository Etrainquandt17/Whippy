#ifndef SCN_STEP_HERO_INFOUTIL_H
#define SCN_STEP_HERO_INFOUTIL_H

namespace scn {
namespace step {
namespace hero {

class Hero;

// TODO: the other functions.
class InfoUtil {
public:
    static void PlayerNumAppearIfNotLonely(Hero& hero);
    static void PlayerNumAppearAll(Hero& hero);
};

}}}  // namespace scn::step::hero

#endif
