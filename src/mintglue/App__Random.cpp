#include "mintglue/App__Random.h"

#include "app/Random.h"
#include "mintglue/WrapNative.h"

namespace mintglue {
namespace App__Random {

void AddOn(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "App.Random", "bool RandBool(float)", RandBool, &app::Random::RandBool);
    MINT_NATIVE_FUNCTION(core, "App.Random", "int Rand(int)", Rand, static_cast<int (*)(int)>(&app::Random::Rand));
    MINT_NATIVE_FUNCTION(core, "App.Random", "int Rand(int,int)", Rand, static_cast<int (*)(int, int)>(&app::Random::Rand));
    MINT_NATIVE_FUNCTION(core, "App.Random", "float RandF(float,float)", RandF, &app::Random::RandF);
    MINT_NATIVE_FUNCTION(core, "App.Random", "float RandNF()", RandNF, &app::Random::RandNF);
    MINT_NATIVE_FUNCTION(core, "App.Random", "float RandAF()", RandAF, &app::Random::RandAF);
}

}}  // namespace mintglue::App__Random
