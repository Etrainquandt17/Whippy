#include "scn/step/enemy/brontoburt/AddOnMint.h"

// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/MintEnemy.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

namespace {

bool t_Custom_IsHitFloor() {
    return MintEnemy::Obj()->mapColl().result().mIsHitFloor;
}

bool t_Custom_IsHitRoof() {
    return MintEnemy::Obj()->mapColl().result().mIsHitRoof;
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.BrontoBurt.Custom", "bool IsHitFloor()", IsHitFloor, t_Custom_IsHitFloor);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.BrontoBurt.Custom", "bool IsHitRoof()", IsHitRoof, t_Custom_IsHitRoof);
}

}

}}}}  // namespace scn::step::enemy::brontoburt
