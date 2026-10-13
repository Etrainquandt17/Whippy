#include "scn/step/hero/mike/utility/Mike.h"
#include "gobj/GearAnim.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"

namespace scn {
namespace step {
namespace hero {
namespace mike {
namespace utility {

void Mike::Set(Hero& hero) {
    switch (hero.abilityManager().abilityKind()) {
    case ABILITY_KIND_MIKE:
        hero.model().weapon().setNodeVisibility(2, true);
        break;
    case 0x1E:
        hero.model().weapon().setNodeVisibility(3, true);
        break;
    case 0x1F:
        hero.model().weapon().setNodeVisibility(4, true);
        break;
    }
}

void Mike::Clear(Hero& hero) {
    hero.model().weapon().setNodeVisibility(2, false);
    hero.model().weapon().setNodeVisibility(3, false);
    hero.model().weapon().setNodeVisibility(4, false);
    hero.model().weapon().anim().clear();
}

}
}
}
}
}
