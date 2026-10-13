#ifndef APP_ROMFONTWRAPPER_H
#define APP_ROMFONTWRAPPER_H

#include "mem/DataBlock.h"
#include "nw4r/ut/ut_RomFont.h"

namespace app {

class RomFontWrapper {
public:
    RomFontWrapper();
    ~RomFontWrapper();

    nw4r::ut::RomFont& font();

private:
    mem::DataBlock mBlock;
    nw4r::ut::RomFont mFont;
};

}

#endif
