#include "mintglue/App__Locale.h"

#include "app/Locale.h"
#include "mintglue/WrapNative.h"

namespace mintglue {
namespace App__Locale {

void AddOn(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "App.Locale", "int GetRegion()", GetRegion, &app::Locale::GetRegion);
    MINT_NATIVE_FUNCTION(core, "App.Locale", "int GetLanguage()", GetLanguage, &app::Locale::GetLanguage);
}

}}  // namespace mintglue::App__Locale
