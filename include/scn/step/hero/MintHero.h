#ifndef SCN_STEP_HERO_MINTHERO_H
#define SCN_STEP_HERO_MINTHERO_H

namespace scn {
namespace step {
namespace hero {

class Hero;

namespace MintHero {

void Register(Hero& obj);
void Unregister(Hero& obj);
Hero& Obj();

}
}
}
}

#endif
