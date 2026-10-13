#ifndef SCN_STEP_HERO_DAMAGEFLASH_H
#define SCN_STEP_HERO_DAMAGEFLASH_H

#include "scn/step/ocoll/Element.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

// TODO: members and the other functions.
class DamageFlash {
public:
    DamageFlash(Hero& hero);

    void update();
    void set(ocoll::Element element);
    void unset();
    bool isValid() const;
};

}
}
}

#endif
