#include "mintglue/App__Random.h"

#include "app/Random.h"
#include "mintglue/WrapNative.h"

using app::Random;

namespace mintglue {
namespace App__Random {

void AddOn(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "App.Random", "bool RandBool(float)", RandBool, &Random::RandBool);
    MINT_NATIVE_FUNCTION(core, "App.Random", "int Rand(int)", Rand, static_cast<int (*)(int)>(&Random::Rand));
    MINT_NATIVE_FUNCTION(core, "App.Random", "int Rand(int,int)", Rand, static_cast<int (*)(int, int)>(&Random::Rand));
    MINT_NATIVE_FUNCTION(core, "App.Random", "float RandF(float,float)", RandF, &Random::RandF);
    MINT_NATIVE_FUNCTION(core, "App.Random", "float RandNF()", RandNF, &Random::RandNF);
    MINT_NATIVE_FUNCTION(core, "App.Random", "float RandAF()", RandAF, &Random::RandAF);
}

}}  // namespace mintglue::App__Random
