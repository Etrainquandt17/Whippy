#ifndef SCN_STEP_HERO_WING_STATESHOT_H
#define SCN_STEP_HERO_WING_STATESHOT_H

namespace scn {
namespace step {
namespace hero {

class Hero;

namespace wing {

class StateShot {
public:
    static bool TryToChangeState(Hero* hero);
};

}
}
}
}

#endif
