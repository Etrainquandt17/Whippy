#ifndef SCN_STEP_HERO_INITIATIVEUTIL_H
#define SCN_STEP_HERO_INITIATIVEUTIL_H

namespace scn {
namespace step {
namespace hero {

class Hero;

class InitiativeUtil {
public:
    static bool IsMine(Hero& hero);
    static bool TryTake(Hero& hero);
    static bool IsSomebody(Hero& hero);
};

}
}
}

#endif
