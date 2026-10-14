#include "scn/step/boss/bonkers/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/math/Vector2.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/bonkers/Param.h"
#include "scn/step/boss/bonkers/ScriptKind.h"
#include "scn/step/boss/bonkers/StateBomb.h"
#include "scn/step/boss/bonkers/StateRainBomb.h"
#include "scn/step/boss/bonkers/StateSwing.h"
#include "scn/step/boss/common/StateAttack.h"
#include "scn/step/boss/common/StateJump.h"
#include "scn/step/boss/common/StateMoveForward.h"
#include "scn/step/ocoll/AttackType.h"

using hel::math::Vector2;

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

namespace {

// TODO: a stand-in, as in gigantedge: the original keeps the boss in a register while the description is made.
inline Boss* t_Boss(Boss& boss) {
    return &boss;
}

void t_SetNextState_AttackHammer() {
    common::StateAttackDesc desc(
        MintBoss::Obj().param().bonkers()._24,
        MintBoss::Obj().param().bonkers()._54,
        MintBoss::Obj().param().bonkers()._5C,
        0.0f,
        0.0f
    );
    MintBoss::Obj().stateChanger().setNextState<common::StateAttack, Boss*, common::StateAttackDesc, ScriptKind>(
        t_Boss(MintBoss::Obj()), desc, SCRIPT_KIND_5
    );
}

void t_SetNextState_AttackFireHammer() {
    common::StateAttackDesc desc(
        MintBoss::Obj().param().bonkers()._24,
        Vector2::ZERO,
        Vector2::ZERO,
        0.0f,
        0.0f
    );
    MintBoss::Obj().stateChanger().setNextState<common::StateAttack, Boss*, common::StateAttackDesc, ScriptKind>(
        t_Boss(MintBoss::Obj()), desc, SCRIPT_KIND_6
    );
}

void t_SetNextState_MoveForward() {
    common::StateMoveDesc desc(MintBoss::Obj().param().bonkers()._48);
    MintBoss::Obj().stateChanger().setNextState<common::StateMoveForward, Boss*, common::StateMoveDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_7
    );
}

void t_SetNextState_StampFoot(f32 x, f32 y) {
    Vector2 v(x, y);
    common::StateJumpDesc desc(
        v,
        MintBoss::Obj().param().bonkers()._24,
        MintBoss::Obj().param().bonkers()._28,
        MintBoss::Obj().param().bonkers()._64,
        Vector2::ZERO,
        Vector2::ZERO,
        true,
        static_cast<common::StateJumpDesc::LandingAnimType>(2),
        false,
        static_cast<ocoll::AttackType>(0x1AB)
    );
    MintBoss::Obj().stateChanger().setNextState<common::StateJump, Boss*, common::StateJumpDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_8
    );
}

void t_SetNextState_JumpBig() {
    MintBoss::Obj().stateChanger().setNextState<StateJumpBigStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Swing() {
    MintBoss::Obj().stateChanger().setNextState<StateSwing, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_SwingPursuit() {
    MintBoss::Obj().stateChanger().setNextState<StateSwingPursuit, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_BombStart() {
    MintBoss::Obj().stateChanger().setNextState<StateBombStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Bomb(f32 x, f32 y, bool a, bool b) {
    StateBomb::Config config;
    config._0 = Vector2(x, y);
    config._8 = a;
    config._9 = b;
    MintBoss::Obj().stateChanger().setNextState<StateBomb, Boss*, StateBomb::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_RainBomb(bool arg) {
    StateRainBomb::Config config;
    config._0 = arg;
    MintBoss::Obj().stateChanger().setNextState<StateRainBombStart, Boss*, StateRainBomb::Config>(&MintBoss::Obj(), config);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Bonkers.SetNextState", "void AttackHammer()", AttackHammer, t_SetNextState_AttackHammer);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Bonkers.SetNextState", "void AttackFireHammer()", AttackFireHammer,
                         t_SetNextState_AttackFireHammer);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Bonkers.SetNextState", "void MoveForward()", MoveForward, t_SetNextState_MoveForward);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Bonkers.SetNextState", "void StampFoot(float,float)", StampFoot, t_SetNextState_StampFoot);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Bonkers.SetNextState", "void JumpBig()", JumpBig, t_SetNextState_JumpBig);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Bonkers.SetNextState", "void Swing()", Swing, t_SetNextState_Swing);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Bonkers.SetNextState", "void SwingPursuit()", SwingPursuit, t_SetNextState_SwingPursuit);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Bonkers.SetNextState", "void BombStart()", BombStart, t_SetNextState_BombStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Bonkers.SetNextState", "void Bomb(float,float,bool,bool)", Bomb, t_SetNextState_Bomb);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Bonkers.SetNextState", "void RainBomb(bool)", RainBomb, t_SetNextState_RainBomb);
}

}

}}}}  // namespace scn::step::boss::bonkers
