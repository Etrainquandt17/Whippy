#include "scn/step/enemy/mahoroahammer/AddOnMint.h"

// Ahead of the Mint headers: strings of inline functions go into .data in the reverse order of their headers.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/mahoroahammer/StateAttack.h"
#include "scn/step/enemy/mahoroahammer/StateBound.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroahammer {

namespace {

void t_SetNextState_Attack(f32 speed, int count) {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*, f32, u32>(MintEnemy::Obj(), speed, count);
}

void t_SetNextState_Bound(f32 x, f32 y) {
    MintEnemy::Obj()->stateChanger().setNextState<StateBound, Enemy*, hel::math::Vector2>(MintEnemy::Obj(), hel::math::Vector2(x, y));
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.MahoroaHammer.SetNextState", "void Attack(float,int)", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.MahoroaHammer.SetNextState", "void Bound(float,float)", Bound, t_SetNextState_Bound);
}

}

}
}
}
}
