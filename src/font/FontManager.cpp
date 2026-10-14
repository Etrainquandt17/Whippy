#include "font/FontManager.h"

#include "font/FontKindUtil.h"
#include "hel/common/ExplicitSingleton.h"
#include "mem/Memory.h"
#include "std/tr1/reference_wrapper.h"

using hel::common::ExplicitSingleton;

namespace font {

FontManager::FontManager()
    : mem::AutoHeapExp(ExplicitSingleton<mem::Memory>::object_->mem2FixHeap(), 0x800, "Font")
    , mFonts(obj()) {}

void FontManager::setup() {
    for (u32 i = 0; i < FONT_KIND_NUM; i++) {
        FontKind kind = static_cast<FontKind>(i);
        mFonts.add<const char*, const char*>(FontKindUtil::FilePath(kind), FontKindUtil::Name(kind));
    }
    for (u32 i = 0; i <= FONT_KIND_MOVIE - 1; i++) {
        mFonts[i].load();
    }
    mPairEBP.construct(FontKindUtil::Name(FONT_KIND_COMMON_EBP), std::tr1::ref(mFonts[FONT_KIND_COMMON_EBP]),
                       std::tr1::ref(mFonts[FONT_KIND_COMMON_EB]));
    mPairEBOLP.construct(FontKindUtil::Name(FONT_KIND_COMMON_EBOLP), std::tr1::ref(mFonts[FONT_KIND_COMMON_EBOLP]),
                         std::tr1::ref(mFonts[FONT_KIND_COMMON_EBOL]));
}

bool FontManager::isSetupFinished() const {
    return mFonts.count() != 0;
}

IFont& FontManager::font(FontKind kind) {
    if (kind == FONT_KIND_COMMON_EBP) {
        return *mPairEBP;
    }
    if (kind == FONT_KIND_COMMON_EBOLP) {
        return *mPairEBOLP;
    }
    return mFonts[kind];
}

}  // namespace font
