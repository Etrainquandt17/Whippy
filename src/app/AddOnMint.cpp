#include "app/AddOnMint.h"

#include "mintglue/App__Alert.h"
#include "mintglue/App__Locale.h"
#include "mintglue/App__Random.h"

namespace app {
namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    mintglue::App__Random::AddOn(core);
    mintglue::App__Alert::AddOn(core);
    mintglue::App__Locale::AddOn(core);
}

}}  // namespace app::AddOnMint
