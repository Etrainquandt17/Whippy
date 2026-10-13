#include "scn/step/enemy/shotzo/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/shotzo/Custom.h"
#include "scn/step/enemy/shotzo/StateAim.h"
#include "scn/step/enemy/shotzo/StateShot.h"

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

namespace {

bool t_Custom_IsPlayerInAimArea() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isPlayerInAimArea();
}

bool t_Custom_IsFixPos() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isFixPos();
}

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Shotzo.SetNextState", "void Shot()", Shot, SetNextState<StateShot>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Shotzo.SetNextState", "void Aim()", Aim, SetNextState<StateAim>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Shotzo.Custom", "bool IsPlayerInAimArea()", IsPlayerInAimArea, t_Custom_IsPlayerInAimArea);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Shotzo.Custom", "bool IsFixPos()", IsFixPos, t_Custom_IsFixPos);
}

}

}
}
}
}
