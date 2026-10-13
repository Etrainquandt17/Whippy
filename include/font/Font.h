#ifndef FONT_FONT_H
#define FONT_FONT_H

#include "font/IFont.h"
#include "hel/common/FixedStringIN.h"
#include "nw4r/ut/ut_ResFont.h"

namespace font {

class Font : public IFont {
public:
    Font(const char* path, const char* name);
    ~Font();

    virtual const char* name() const;
    virtual void load();
    virtual void unload();
    virtual bool loaded() const;
    virtual nw4r::ut::Font& font();

private:
    hel::common::FixedStringIN<char, 80> mPath;
    hel::common::FixedStringIN<char, 32> mName;
    nw4r::ut::ResFont mFont;
    bool mLoaded;
};

}

#endif
