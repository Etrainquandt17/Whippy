#include "scn/step/enemy/babut/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/babut/Custom.h"
#include "scn/step/enemy/babut/StateAttack.h"
#include "scn/step/enemy/babut/StateDoubterAppear.h"
#include "scn/step/enemy/babut/StateEscape.h"
#include "scn/step/enemy/babut/StateFlySinCurve.h"
#include "scn/step/enemy/babut/StateHang.h"
#include "scn/step/enemy/babut/StatePursuit.h"
#include "scn/step/enemy/babut/StateStandBack.h"
#include "scn/step/enemy/babut/StateTakeOff.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace babut {

namespace {

bool t_IsPlayerInArea() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isPlayerInArea();
}

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Babut.SetNextState", "void Attack()", Attack, SetNextState<StateAttack>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Babut.SetNextState", "void DoubterAppear()", DoubterAppear, SetNextState<StateDoubterAppear>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Babut.SetNextState", "void Escape()", Escape, SetNextState<StateEscape>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Babut.SetNextState", "void FlySinCurve()", FlySinCurve, SetNextState<StateFlySinCurve>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Babut.SetNextState", "void Hang()", Hang, SetNextState<StateHang>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Babut.SetNextState", "void Pursuit()", Pursuit, SetNextState<StatePursuit>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Babut.SetNextState", "void StandBack()", StandBack, SetNextState<StateStandBack>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Babut.SetNextState", "void TakeOff()", TakeOff, SetNextState<StateTakeOff>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Babut.Custom", "bool IsPlayerInArea()", IsPlayerInArea, t_IsPlayerInArea);
}

}

}}}}  // namespace scn::step::enemy::babut
