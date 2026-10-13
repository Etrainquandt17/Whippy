#ifndef SCN_STEP_HERO_NEEDLE_STATEDASH_H
#define SCN_STEP_HERO_NEEDLE_STATEDASH_H

namespace scn {
namespace step {
namespace hero {

class Hero;

namespace needle {

class StateDash {
public:
    static bool TryToChangeState(Hero* hero);
};

}
}
}
}

#endif
