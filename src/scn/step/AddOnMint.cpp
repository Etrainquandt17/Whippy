#include "scn/step/AddOnMint.h"

#include "scn/step/boss/AddOnMint.h"
#include "scn/step/camera/AddOnMint.h"
#include "scn/step/core/AddOnMint.h"

// TODO: these belong in the headers of their units, which do not exist yet.
namespace scn {
namespace step {

namespace chara {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}
}

namespace enemy {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}
}

namespace hero {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}
}

namespace sfx {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}
}

namespace vacuum {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}
}

namespace gimmick {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}
}

namespace ocoll {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}
}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    boss::AddOnMint::RegisterAll(core);
    camera::AddOnMint::RegisterAll(core);
    chara::AddOnMint::RegisterAll(core);
    core::AddOnMint::RegisterAll(core);
    enemy::AddOnMint::RegisterAll(core);
    hero::AddOnMint::RegisterAll(core);
    sfx::AddOnMint::RegisterAll(core);
    vacuum::AddOnMint::RegisterAll(core);
    gimmick::AddOnMint::RegisterAll(core);
    ocoll::AddOnMint::RegisterAll(core);
}

}
}
}
