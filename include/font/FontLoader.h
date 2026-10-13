#ifndef FONT_FONTLOADER_H
#define FONT_FONTLOADER_H

#include "font/FontKind.h"

namespace font {

class FontLoader {
public:
    FontLoader(FontKind kind);
    ~FontLoader();

private:
    FontKind mKind;
};

}  // namespace font

#endif
