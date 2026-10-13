#ifndef FONT_FONTMANAGER_H
#define FONT_FONTMANAGER_H

#include "font/Font.h"
#include "font/FontKind.h"
#include "font/PairFont.h"
#include "hel/common/Array.h"
#include "hel/common/ArrayUtil.h"
#include "mem/AutoHeapExp.h"
#include "mem/ExplicitAutoDeleteArray.h"
#include "types.h"
#include "util/PlacementNew.h"

// TODO: mem/ExplicitAutoDeleteArray.h keeps its pointers in a plain array, which leaves out the range check of
// hel::common::Array, and has no add() for two arguments. Until it changes, the instance for the fonts is here.
namespace mem {

template <int N>
class ExplicitAutoDeleteArray<font::Font, N> {
public:
    ExplicitAutoDeleteArray(IAllocator& allocator) : mAllocator(&allocator), mCount(0), mArray() {}
    ~ExplicitAutoDeleteArray();

    template <typename A1, typename A2>
    void add(A1 a1, A2 a2) {
        mArray[mCount] = new (*mAllocator) font::Font(a1, a2);
        mCount++;
    }

    font::Font& operator[](u32 index) {
        hel::common::ArrayUtil::RangeCheck(index, mCount);
        return *mArray[index];
    }
    u32 count() const { return mCount; }

private:
    IAllocator* mAllocator;
    u32 mCount;
    hel::common::Array<font::Font*, N> mArray;
};

}

namespace font {

// The Korean version has one font fewer.
class FontManager : public mem::AutoHeapExp {
public:
    FontManager();
    ~FontManager();

    void setup();
    bool isSetupFinished() const;
    IFont& font(FontKind kind);

private:
    mem::ExplicitAutoDeleteArray<Font, FONT_KIND_NUM> mFonts;
    util::PlacementNew<PairFont> mPairEBP;
    util::PlacementNew<PairFont> mPairEBOLP;
};

}

#endif
