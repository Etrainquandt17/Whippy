#ifndef FONT_FONTKINDUTIL_H
#define FONT_FONTKINDUTIL_H

#include "font/FontKind.h"
#include "hel/common/FixedString.h"

namespace font {

namespace FontKindUtil {

hel::common::FixedString<80> FilePath(FontKind kind);
const char* Name(FontKind kind);

}

}  // namespace font

#endif
