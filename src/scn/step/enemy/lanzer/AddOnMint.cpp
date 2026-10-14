#include "scn/step/enemy/lanzer/AddOnMint.h"

#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/lanzer/StateAttack.h"
#include "scn/step/enemy/lanzer/StateWait.h"
#include "scn/step/enemy/lanzer/StateWalk.h"
#include "scn/step/enemy/lanzer/StateWalkAround.h"

using hel::math::Direction3;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

namespace {

void t_SetNextState_Wait() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWait, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Walk() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalk, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_WalkAround() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalkAround, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

void t_Custom_AttackEffect() {
    f32 sign = MintEnemy::Obj()->target().getSign();
    Direction3 dir(Vector3(sign, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, -sign));
    MintEnemy::Obj()->effect().state().requestND(static_cast<effect::Kind>(0x50F), 3, dir);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Lanzer.SetNextState", "void Wait()", Wait, t_SetNextState_Wait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Lanzer.SetNextState", "void Walk()", Walk, t_SetNextState_Walk);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Lanzer.SetNextState", "void WalkAround()", WalkAround, t_SetNextState_WalkAround);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Lanzer.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Lanzer.Custom", "void AttackEffect()", AttackEffect, t_Custom_AttackEffect);
}

}

}}}}  // namespace scn::step::enemy::lanzer
