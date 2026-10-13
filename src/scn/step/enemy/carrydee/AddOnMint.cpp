#include "scn/step/enemy/carrydee/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/carrydee/Custom.h"

namespace scn {
namespace step {
namespace enemy {
namespace carrydee {

namespace {

bool t_Custom_IsHaveKey() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isHaveKey();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.CarryDee.Custom", "bool IsHaveKey()", IsHaveKey, t_Custom_IsHaveKey);
}

}

}}}}  // namespace scn::step::enemy::carrydee
