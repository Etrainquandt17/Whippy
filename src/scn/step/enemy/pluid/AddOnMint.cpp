#include "scn/step/enemy/pluid/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/pluid/Custom.h"
#include "scn/step/enemy/pluid/StateJump.h"

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

namespace {

void t_SetNextState_Jump() {
    MintEnemy::Obj()->stateChanger().setNextState<StateJump, Enemy*>(MintEnemy::Obj());
}

void t_Custom_SetRotate(f32 rotate) {
    hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setRotate(rotate);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Pluid.SetNextState", "void Jump()", Jump, t_SetNextState_Jump);
    // TODO: the wrapper of SetRotate differs: with Regset::internal_getFR expanded in it, the original keeps the argument's index in r31 and the Regset in r30.
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Pluid.Custom", "void SetRotate(float)", SetRotate, t_Custom_SetRotate);
}

}

}}}}  // namespace scn::step::enemy::pluid
