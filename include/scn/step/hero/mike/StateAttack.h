#ifndef SCN_STEP_HERO_MIKE_STATEATTACK_H
#define SCN_STEP_HERO_MIKE_STATEATTACK_H

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace mike {

class StateAttack {
public:
    static bool TryToChangeState(Hero* hero);
    static bool TryToChangeState(Hero* hero, bool isCharged);
};

}
}
}
}

#endif
