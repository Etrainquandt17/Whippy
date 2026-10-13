#include "scn/step/enemy/glunk/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/glunk/Custom.h"
#include "scn/step/enemy/glunk/StateShot.h"

namespace scn {
namespace step {
namespace enemy {
namespace glunk {

namespace {

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

void t_Custom_SetRotate(f32 value) {
    hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setRotate(value);
}

bool t_Custom_CheckExistLand() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).checkExistLand();
}

bool t_IsCurrentFall() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isCurrentFall();
}

void t_SetIsCurrentFall(bool value) {
    hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setIsCurrentFall(value);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Glunk.SetNextState", "void Shot()", Shot, SetNextState<StateShot>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Glunk.Custom", "void SetRotate(float)", SetRotate, t_Custom_SetRotate);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Glunk.Custom", "bool CheckExistLand()", CheckExistLand, t_Custom_CheckExistLand);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Glunk.Custom", "bool IsCurrentFall()", IsCurrentFall, t_IsCurrentFall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Glunk.Custom", "void SetIsCurrentFall(bool)", SetIsCurrentFall, t_SetIsCurrentFall);
}

}

}
}
}
}
