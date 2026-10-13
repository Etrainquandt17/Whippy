#ifndef NW4R_LYT_TEXTBOX_H
#define NW4R_LYT_TEXTBOX_H

#include "nw4r/lyt/lyt_types.h"
#include "types.h"

namespace nw4r {
namespace lyt {

class TextBox {
public:
    const Size& GetFontSize() const { return mFontSize; }
    void SetFontSize(const Size& fontSize) { mFontSize = fontSize; }
    f32 GetCharSpace() const { return mCharSpace; }
    void SetCharSpace(f32 space) { mCharSpace = space; }

private:
    u8 _0[0xE8];
    Size mFontSize;
    f32 mLineSpace;
    f32 mCharSpace;
};

}
}

#endif
