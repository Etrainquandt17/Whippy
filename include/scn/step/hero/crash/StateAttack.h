#ifndef SCN_STEP_HERO_CRASH_STATEATTACK_H
#define SCN_STEP_HERO_CRASH_STATEATTACK_H

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace crash {

class StateAttack {
public:
    static bool TryToChangeState(Hero* hero, bool isCharged);
};

}
}
}
}

#endif
