#include "hel/mint/AddOnMathMath.h"

#include "hel/math/Math.h"
#include "hel/mint/WrapNative.h"

using hel::math::Math;

namespace hel {
namespace mint {

namespace {

float t_SinRadF(float rad) {
    return Math::SinF(rad);
}

float t_CosRadF(float rad) {
    return Math::CosF(rad);
}

float t_TanRadF(float rad) {
    return Math::TanF(rad);
}

float t_SinDegF(float deg) {
    return Math::SinF(Math::DegToRad(deg));
}

float t_CosDegF(float deg) {
    return Math::CosF(Math::DegToRad(deg));
}

float t_TanDegF(float deg) {
    return Math::TanF(Math::DegToRad(deg));
}

bool t_EqZero(float value) {
    return Math::EqZero(value);
}

}

namespace AddOnMathMath {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Math", "float SinRadF(float)", SinRadF, t_SinRadF);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Math", "float CosRadF(float)", CosRadF, t_CosRadF);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Math", "float TanRadF(float)", TanRadF, t_TanRadF);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Math", "float SinDegF(float)", SinDegF, t_SinDegF);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Math", "float CosDegF(float)", CosDegF, t_CosDegF);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Math", "float TanDegF(float)", TanDegF, t_TanDegF);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Math", "bool EqZero(float)", EqZero, t_EqZero);
}

}

}}  // namespace hel::mint
