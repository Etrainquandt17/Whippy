#ifndef SCN_STEP_HERO_BOSSDEMOCTRL_H
#define SCN_STEP_HERO_BOSSDEMOCTRL_H

#include "scn/step/hero/BossDemoSignalKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class BossDemoCtrl {
public:
    // TODO: the names of the enumerators.
    enum DemoKind {
        DEMO_KIND_0,
        DEMO_KIND_1,
    };

    void setSignal(BossDemoSignalKind kind);
    bool isSilent() const;
    void startBossDemoMode(f32, f32, DemoKind kind);
    void endBossDemoMode();
};

}
}
}

#endif
