#include "scn/step/enemy/armordee/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/armordee/Custom.h"

namespace scn {
namespace step {
namespace enemy {
namespace armordee {

namespace {

f32 t_GetFrameRate() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).getFrameRate();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.ArmorDee.Custom", "float GetFrameRate()", GetFrameRate, t_GetFrameRate);
}

}

}}}}  // namespace scn::step::enemy::armordee
