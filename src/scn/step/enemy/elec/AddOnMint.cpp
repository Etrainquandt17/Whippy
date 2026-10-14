#include "scn/step/enemy/elec/AddOnMint.h"

// Ahead of the Mint headers: strings of inline functions go into .data in the reverse order of their headers.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/elec/ParamData.h"
#include "scn/step/ocoll/AttackType.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace elec {

namespace {

inline Enemy& obj() {
    return *MintEnemy::Obj();
}

void t_Custom_SetViewOffset(f32 x, f32 y) {
    obj().model().setViewOffset(Vector3(x, y, 0.0f));
}

void t_Custom_AttackEffect0() {
    obj().objColl().clearAttack();
    obj().objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x1A2));
    obj().objColl().addAttack(0, 1, 0.3f * Utility::GetModelScaleBySizeType(obj()));
    obj().effect().state().requestN(static_cast<effect::Kind>(0x4FA), 1);
}

void t_Custom_AttackEffect1() {
    obj().objColl().clearAttack();
    obj().objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x1A2));
    obj().objColl().addAttack(0, 1, obj().param().elec()._58 * Utility::GetModelScaleBySizeType(obj()));
    obj().effect().state().requestN(static_cast<effect::Kind>(0x4F9), 1);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Elec.Custom", "void SetViewOffset(float,float)", SetViewOffset, t_Custom_SetViewOffset);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Elec.Custom", "void AttackEffect0()", AttackEffect0, t_Custom_AttackEffect0);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Elec.Custom", "void AttackEffect1()", AttackEffect1, t_Custom_AttackEffect1);
}

}

}}}}  // namespace scn::step::enemy::elec
