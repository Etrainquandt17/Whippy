#include "font/FontKindUtil.h"

namespace font {

namespace {

struct FontContext {
    const char* dir;
    const char* name;
    const char* fileName;
};

const FontContext T_FONT_CONTEXT_TABLE[FONT_KIND_NUM] = {
    { "jp/", "CommonEB.brfnt", "CommonEB.brfnt" },
    { "jp/", "CommonEBP.brfnt", "CommonEBP_Num.brfnt" },
    { "jp/", "CommonEBOL.brfnt", "CommonEBOL.brfnt" },
    { "jp/", "CommonEBOLP.brfnt", "CommonEBOLP_Num.brfnt" },
    { "jp/", "ExternalChar.brfnt", "ExternalChar.brfnt" },
#ifndef VERSION_SUKK01
    { "jp/", "Ruby.brfnt", "Ruby.brfnt" },
#endif
    { "jp/", "Movie.brfnt", "Movie.brfnt" },
    { "jp/", "StaffCredits.brfnt", "StaffCredits.brfnt" },
    { "jp/", "GunShooting.brfnt", "GunShooting.brfnt" },
    { "jp/", "Setsuna1.brfnt", "Setsuna1.brfnt" },
    { "jp/", "Setsuna2.brfnt", "Setsuna2.brfnt" },
    { "jp/", "Setsuna3.brfnt", "Setsuna3.brfnt" },
};

const FontContext t_context(FontKind kind) {
    return T_FONT_CONTEXT_TABLE[kind];
}

}

namespace FontKindUtil {

hel::common::FixedString<80> FilePath(FontKind kind) {
    const FontContext context = t_context(kind);
    return hel::common::FixedStringIN<char, 80>::FromFormat("font/%s%s", context.dir, context.fileName);
}

const char* Name(FontKind kind) {
    return t_context(kind).name;
}

}

}
