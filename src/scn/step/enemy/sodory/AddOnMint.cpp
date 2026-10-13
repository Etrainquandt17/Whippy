#include "scn/step/enemy/sodory/AddOnMint.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/sodory/Custom.h"
#include "scn/step/enemy/sodory/StateAttack.h"
#include "scn/step/enemy/sodory/StateFly.h"
#include "scn/step/enemy/sodory/StateGroundAttack.h"
#include "scn/step/enemy/sodory/StateWait.h"
#include "scn/step/enemy/sodory/StateWalkAround.h"

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

namespace {

void t_SetNextState_Wait() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWait, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_WalkAround() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalkAround, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Fly() {
    MintEnemy::Obj()->stateChanger().setNextState<StateFly, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_GroundAttack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateGroundAttack, Enemy*>(MintEnemy::Obj());
}

// TODO: name the kind. It is one higher in the Korean build.
#ifdef VERSION_SUKK01
const effect::Kind t_attackEffectKind = static_cast<effect::Kind>(0x64F);
#else
const effect::Kind t_attackEffectKind = static_cast<effect::Kind>(0x64E);
#endif

void t_Custom_AttackEffect() {
    f32 sign = MintEnemy::Obj()->target().getSign();
    hel::math::Direction3 dir(hel::math::Vector3(sign, 0.0f, 0.0f), hel::math::Vector3(0.0f, 1.0f, 0.0f), hel::math::Vector3(0.0f, 0.0f, -sign));
    MintEnemy::Obj()->effect().state().requestND(t_attackEffectKind, 0, dir);
}

void t_Custom_SetDirection() {
    hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setDirection();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Sodory.SetNextState", "void Wait()", Wait, t_SetNextState_Wait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Sodory.SetNextState", "void WalkAround()", WalkAround, t_SetNextState_WalkAround);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Sodory.SetNextState", "void Fly()", Fly, t_SetNextState_Fly);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Sodory.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Sodory.SetNextState", "void GroundAttack()", GroundAttack, t_SetNextState_GroundAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Sodory.Custom", "void AttackEffect()", AttackEffect, t_Custom_AttackEffect);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Sodory.Custom", "void SetDirection()", SetDirection, t_Custom_SetDirection);
}

}

}
}
}
}
