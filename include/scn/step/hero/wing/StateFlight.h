#ifndef SCN_STEP_HERO_WING_STATEFLIGHT_H
#define SCN_STEP_HERO_WING_STATEFLIGHT_H

namespace scn {
namespace step {
namespace hero {

class Hero;

namespace wing {

class StateFlight {
public:
    static bool TryToChangeState(Hero* hero);
};

}
}
}
}

#endif
