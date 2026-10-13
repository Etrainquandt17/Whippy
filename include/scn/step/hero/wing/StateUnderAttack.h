#ifndef SCN_STEP_HERO_WING_STATEUNDERATTACK_H
#define SCN_STEP_HERO_WING_STATEUNDERATTACK_H

namespace scn {
namespace step {
namespace hero {

class Hero;

namespace wing {

class StateUnderAttack {
public:
    static bool TryToChangeState(Hero* hero);
};

}
}
}
}

#endif
