#include "scn/step/enemy/knucklejoe/AddOnMint.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/knucklejoe/Custom.h"
#include "scn/step/enemy/knucklejoe/StateAttack.h"
#include "scn/step/enemy/knucklejoe/StateWalk.h"
#include "scn/step/enemy/knucklejoe/StateWalkStepBack.h"

namespace scn {
namespace step {
namespace enemy {
namespace knucklejoe {

namespace {

void t_SetNextState_Walk() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalk, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_WalkStepBack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalkStepBack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

void t_Custom_AttackEffect(effect::Kind kind) {
    f32 sign = MintEnemy::Obj()->target().getSign();
    hel::math::Direction3 dir(hel::math::Vector3(sign, 0.0f, 0.0f), hel::math::Vector3(0.0f, 1.0f, 0.0f), hel::math::Vector3(0.0f, 0.0f, -sign));
    MintEnemy::Obj()->effect().state().requestND(kind, 0, dir);
}

void t_Custom_Shot() {
    hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).shot();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.KnuckleJoe.SetNextState", "void Walk()", Walk, t_SetNextState_Walk);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.KnuckleJoe.SetNextState", "void WalkStepBack()", WalkStepBack, t_SetNextState_WalkStepBack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.KnuckleJoe.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    // TODO: the wrapper has r30 and r31 the other way round. It matches when the one-argument wrapper in
    // WrapNative.h reads its argument through an inline function; MINT_ARG itself has to stay as it is.
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.KnuckleJoe.Custom", "void AttackEffect(int)", AttackEffect, t_Custom_AttackEffect);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.KnuckleJoe.Custom", "void Shot()", Shot, t_Custom_Shot);
}

}

}
}
}
}
