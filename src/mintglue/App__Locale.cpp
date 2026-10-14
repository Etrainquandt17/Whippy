#include "mintglue/App__Locale.h"

#include "app/Locale.h"
#include "mintglue/WrapNative.h"

using app::Locale;

namespace mintglue {
namespace App__Locale {

void AddOn(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "App.Locale", "int GetRegion()", GetRegion, &Locale::GetRegion);
    MINT_NATIVE_FUNCTION(core, "App.Locale", "int GetLanguage()", GetLanguage, &Locale::GetLanguage);
}

}}  // namespace mintglue::App__Locale
