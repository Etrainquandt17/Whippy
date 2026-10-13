#ifndef FONT_PAIRFONT_H
#define FONT_PAIRFONT_H

#include "font/IFont.h"
#include "hel/common/FixedStringIN.h"
#include "nw4r/ut/ut_PairFont.h"

namespace font {

class Font;

class PairFont : public IFont {
public:
    PairFont(const char* name, Font& primary, Font& secondary);

    virtual const char* name() const;
    virtual void load();
    virtual void unload();
    virtual bool loaded() const;
    virtual nw4r::ut::Font& font();

private:
    hel::common::FixedStringIN<char, 32> mName;
    nw4r::ut::PairFont mFont;
};

}  // namespace font

#endif
