#include "scn/step/hero/mike/utility/Hat.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"

namespace scn {
namespace step {
namespace hero {
namespace mike {
namespace utility {

void Hat::Set(Hero& hero) {
    Clear(hero);
    switch (hero.abilityManager().abilityKind()) {
    case ABILITY_KIND_MIKE:
        hero.model().hat().setNodeVisibility(1, true);
        break;
    case 0x1E:
        hero.model().hat().setNodeVisibility(2, true);
        break;
    case 0x1F:
        hero.model().hat().setNodeVisibility(3, true);
        break;
    }
}

void Hat::Clear(Hero& hero) {
    hero.model().hat().setNodeVisibility(1, false);
    hero.model().hat().setNodeVisibility(2, false);
    hero.model().hat().setNodeVisibility(3, false);
}

void Hat::Wait(Hero& hero) {
    hero.model().hat().setNodeVisibility(1, false);
    hero.model().hat().setNodeVisibility(2, true);
    hero.model().hat().setNodeVisibility(3, false);
}

}
}
}
}
}
