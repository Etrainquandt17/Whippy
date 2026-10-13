#include "scn/step/enemy/sisterbound/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/sisterbound/Custom.h"
#include "scn/step/enemy/sisterbound/StateJumpStart.h"
#include "scn/step/enemy/sisterbound/StateLanding.h"

namespace scn {
namespace step {
namespace enemy {
namespace sisterbound {

namespace {

void t_SetNextState_JumpStart() {
    MintEnemy::Obj()->stateChanger().setNextState<StateJumpStart, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Landing() {
    MintEnemy::Obj()->stateChanger().setNextState<StateLanding, Enemy*>(MintEnemy::Obj());
}

bool t_Custom_IsChangeDir() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isChangeDir();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.SisterBound.SetNextState", "void JumpStart()", JumpStart, t_SetNextState_JumpStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.SisterBound.SetNextState", "void Landing()", Landing, t_SetNextState_Landing);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.SisterBound.Custom", "bool IsChangeDir()", IsChangeDir, t_Custom_IsChangeDir);
}

}

}
}
}
}
