#include "hel/mint/AddOnCast.h"

#include "hel/mint/WrapNative.h"

namespace hel {
namespace mint {

namespace {

// The local keeps the wrapper calling this: a function that is one expression of an integer
// argument is expanded into it.
float t_I2F(int value) {
    float result = static_cast<float>(value);
    return result;
}

int t_F2I(float value) {
    return static_cast<int>(value);
}

}

namespace AddOnCast {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "HEL.Cast", "float I2F(int)", I2F, t_I2F);
    MINT_NATIVE_FUNCTION(core, "HEL.Cast", "int F2I(float)", F2I, t_F2I);
}

}

}
}
