#ifndef SCN_WMAP_INFO_LEVELTITLE_H
#define SCN_WMAP_INFO_LEVELTITLE_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "scn/wmap/MapKind.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace wmap {
namespace info {

class LevelTitle {
public:
    enum TextType {
        TEXT_TYPE_0,
    };

    LevelTitle(mem::IAllocator& allocator, const lyt::PaneAccessor& parent);

    void updateFrame();
    void setMapKind(MapKind kind);
    bool isOpen() const;
    void setTextType(TextType type);
    void textOpen(TextType type);
    void textClose();
    void open();

private:
    void mfSetText();
    void mfUpdateVisibility();
    void mfTextOpen();
    void mfTextClose();

    bool mfIsTextShown() const { return mTextState == 1 || mTextState == 2; }
    bool mfIsTextBusy() const { return mfIsTextShown() || mTextState == 3; }

    lyt::Layout mLayout;
    MapKind mMapKind;
    int mState;
    int mTextState;
    TextType mTextType;
    bool _1A0;
    bool _1A1;
};

}
}
}

#endif
