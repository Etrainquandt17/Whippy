#define UTIL_STATECHANGER_FACTORY_ARGUMENTS_BY_REFERENCE
#include "scn/step/enemy/fattybufferjr/AddOnMint.h"

// Ahead of the Mint headers: strings of inline functions go into .data in the reverse order of their headers.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/fattybufferjr/StateEscapeNear.h"
#include "scn/step/enemy/fattybufferjr/StateJump.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferjr {

namespace {

void t_SetNextState_Jump(f32 x, f32 y) {
    MintEnemy::Obj()->stateChanger().setNextState<StateJump, Enemy*, Vector3>(MintEnemy::Obj(), Vector3(x, y, 0.0f));
}

void t_SetNextState_EscapeNear() {
    MintEnemy::Obj()->stateChanger().setNextState<StateEscapeNear, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.FattyBufferJr.SetNextState", "void Jump(float,float)", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.FattyBufferJr.SetNextState", "void EscapeNear()", EscapeNear, t_SetNextState_EscapeNear);
}

}

}}}}  // namespace scn::step::enemy::fattybufferjr
