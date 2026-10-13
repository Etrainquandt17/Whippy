#include "scn/step/enemy/bouncy/AddOnMint.h"

#include "gobj/Move.h"
// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/bouncy/StateGrandLowperEscapeStart.h"
#include "scn/step/enemy/bouncy/StateJump.h"
#include "scn/step/enemy/bouncy/StateLanding.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

namespace {

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

void t_Custom_SetSpeedH(f32 speed) {
    MintEnemy::Obj()->move().setSpeedH(speed);
}

void t_Custom_SetSpeedV(f32 speed) {
    MintEnemy::Obj()->move().setSpeedV(speed);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bouncy.SetNextState", "void Jump()", Jump, SetNextState<StateJump>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bouncy.SetNextState", "void Landing()", Landing, SetNextState<StateLanding>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bouncy.Custom", "void SetSpeedH(float)", SetSpeedH, t_Custom_SetSpeedH);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bouncy.Custom", "void SetSpeedV(float)", SetSpeedV, t_Custom_SetSpeedV);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bouncy.SetNextState", "void GrandLowperEscape()", GrandLowperEscape, SetNextState<StateGrandLowperEscapeStart>);
}

}

}}}}  // namespace scn::step::enemy::bouncy
