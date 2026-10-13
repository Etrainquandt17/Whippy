#include "scn/step/enemy/mahoroamagicball/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/mahoroamagicball/Custom.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

namespace {

bool t_Custom_IsPhase2nd() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isPhase2nd();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.MahoroaMagicBall.Custom", "bool IsPhase2nd()", IsPhase2nd, t_Custom_IsPhase2nd);
}

}

}}}}  // namespace scn::step::enemy::mahoroamagicball
