#ifndef SCN_STEP_HERO_ABILITYKINDUTIL_H
#define SCN_STEP_HERO_ABILITYKINDUTIL_H

#include "pause/ManualKind.h"
#include "scn/step/hero/AbilityKind.h"

namespace scn {
namespace step {
namespace hero {

class AbilityKindUtil {
public:
    static const char* FDNName(AbilityKind kind);
    static bool IsSuper(AbilityKind kind);
    static bool IsKirbyAbility(AbilityKind kind);
    static pause::ManualKind ToManualKind(AbilityKind kind, bool, bool);
};

}
}
}

#endif
