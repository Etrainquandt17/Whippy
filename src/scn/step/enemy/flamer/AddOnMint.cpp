#include "scn/step/enemy/flamer/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/flamer/Custom.h"
#include "scn/step/enemy/flamer/StateAgony.h"
#include "scn/step/enemy/flamer/StateAttack.h"
#include "scn/step/enemy/flamer/StateChase.h"
#include "scn/step/enemy/flamer/StateMove.h"

using hel::common::DynamicCastToRef;
using hel::math::Direction3;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

namespace {

inline Enemy& obj() {
    return *MintEnemy::Obj();
}

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_ChaseOrAgony() {
    if (!DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isAttackEnd()) {
        SetNextState<StateChase>();
    } else {
        SetNextState<StateAgony>();
    }
}

bool t_Custom_IsMove() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isMove();
}

void t_Custom_Dead() {
    DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).dead();
}

void t_Custom_SetViewOffset(f32 x, f32 y) {
    obj().model().setViewOffset(Vector3(x, y, 0.0f));
}

void t_Custom_ChaseEffect() {
    obj().effect().state().requestN(static_cast<effect::Kind>(0x194), 1);
}

void t_Custom_AttackREffect() {
    Direction3 dir(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f));
    obj().effect().state().requestND(static_cast<effect::Kind>(0x192), 2, dir);
}

void t_Custom_AttackLEffect() {
    Direction3 dir(Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f));
    obj().effect().state().requestND(static_cast<effect::Kind>(0x192), 2, dir);
}

}

}

namespace common {

namespace {

// TODO: this unit emits its own copy of the function that common/AddOnMint.cpp binds, under the same name,
// so the original has it inline in a header that both include. Its factory's table sits in .data as if
// that header came after the functions above.
inline void t_SetNextState_Fall() {
    MintEnemy::Obj()->stateChanger().setNextState<StateFall, Enemy*>(MintEnemy::Obj());
}

}

}

namespace flamer {

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.SetNextState", "void MoveCWR()", MoveCWR, SetNextState<StateMoveCWR>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.SetNextState", "void MoveCCW()", MoveCCW, SetNextState<StateMoveCCW>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.SetNextState", "void Chase()", Chase, SetNextState<StateChase>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.SetNextState", "void Attack()", Attack, SetNextState<StateAttack>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.SetNextState", "void Agony()", Agony, SetNextState<StateAgony>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.SetNextState", "void Fall()", Fall, common::t_SetNextState_Fall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.SetNextState", "void ChaseOrAgony()", ChaseOrAgony, t_SetNextState_ChaseOrAgony);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.Custom", "bool IsMove()", IsMove, t_Custom_IsMove);
    // The game binds the getter here: a script's SetIsMove(bool) changes nothing.
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.Custom", "void SetIsMove(bool)", SetIsMove, reinterpret_cast<void (*)(bool)>(t_Custom_IsMove));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.Custom", "void Dead()", Dead, t_Custom_Dead);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.Custom", "void SetViewOffset(float,float)", SetViewOffset, t_Custom_SetViewOffset);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.Custom", "void ChaseEffect()", ChaseEffect, t_Custom_ChaseEffect);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.Custom", "void AttackREffect()", AttackREffect, t_Custom_AttackREffect);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flamer.Custom", "void AttackLEffect()", AttackLEffect, t_Custom_AttackLEffect);
}

}

}}}}  // namespace scn::step::enemy::flamer
