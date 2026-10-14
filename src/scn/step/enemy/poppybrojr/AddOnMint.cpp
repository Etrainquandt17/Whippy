#include "scn/step/enemy/poppybrojr/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/poppybrojr/Custom.h"
#include "scn/step/enemy/poppybrojr/StateMove.h"
#include "scn/step/enemy/poppybrojr/StateThrow.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojr {

namespace {

int t_Custom_SetWaitTime() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setWaitTime();
}

bool t_Custom_IsThrowValid() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isThrowValid();
}

void t_Custom_RequestBomb() {
    DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).requestBomb();
}

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.PoppyBroJr.SetNextState", "void Move()", Move, SetNextState<StateMove>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.PoppyBroJr.SetNextState", "void Throw()", Throw, SetNextState<StateThrow>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.PoppyBroJr.Custom", "int SetWaitTime()", SetWaitTime, t_Custom_SetWaitTime);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.PoppyBroJr.Custom", "bool IsThrowValid()", IsThrowValid, t_Custom_IsThrowValid);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.PoppyBroJr.Custom", "void RequestBomb()", RequestBomb, t_Custom_RequestBomb);
}

}

}}}}  // namespace scn::step::enemy::poppybrojr
