#include "nw4r/ut.h"

#include "nw4r/ut/ut_PairFont.h"

namespace nw4r {
namespace ut {

PairFont::PairFont(Font *pFirst, Font *pSecond) : mFirst(pFirst), mSecond(pSecond), mAlternateWithFirst(true) {
    InitReaderFunc(mFirst->GetEncoding());
}

PairFont::~PairFont() {}

int PairFont::GetWidth() const {
    return Max(mFirst->GetWidth(), mSecond->GetWidth());
}

int PairFont::GetHeight() const {
    return Max(mFirst->GetHeight(), mSecond->GetHeight());
}

int PairFont::GetAscent() const {
    return mFirst->GetHeight() >= mSecond->GetHeight() ? mFirst->GetAscent() : mSecond->GetAscent();
}

int PairFont::GetDescent() const {
    return mFirst->GetHeight() >= mSecond->GetHeight() ? mFirst->GetDescent() : mSecond->GetDescent();
}

int PairFont::GetBaselinePos() const {
    return mFirst->GetHeight() >= mSecond->GetHeight() ? mFirst->GetBaselinePos() : mSecond->GetBaselinePos();
}

int PairFont::GetCellHeight() const {
    return mFirst->GetHeight() >= mSecond->GetHeight() ? mFirst->GetCellHeight() : mSecond->GetCellHeight();
}

int PairFont::GetCellWidth() const {
    return mFirst->GetWidth() >= mSecond->GetWidth() ? mFirst->GetCellWidth() : mSecond->GetCellWidth();
}

int PairFont::GetMaxCharWidth() const {
    return Max(mFirst->GetMaxCharWidth(), mSecond->GetMaxCharWidth());
}

Font::Type PairFont::GetType() const {
    return TYPE_PAIR;
}

GXTexFmt PairFont::GetTextureFormat() const {
    return mFirst->GetTextureFormat();
}

int PairFont::GetLineFeed() const {
    return Max(mFirst->GetLineFeed(), mSecond->GetLineFeed());
}

CharWidths PairFont::GetDefaultCharWidths() const {
    if (mFirst->GetWidth() >= mSecond->GetWidth()) {
        return mFirst->GetDefaultCharWidths();
    } else {
        return mSecond->GetDefaultCharWidths();
    }
}

void PairFont::SetDefaultCharWidths(const CharWidths &widths) {
    mFirst->SetDefaultCharWidths(widths);
    mSecond->SetDefaultCharWidths(widths);
}

bool PairFont::SetAlternateChar(u16 c) {
    bool first = mFirst->SetAlternateChar(c);
    bool second = mSecond->SetAlternateChar(c);

    if (first) {
        mAlternateWithFirst = true;
        return true;
    } else if (second) {
        mAlternateWithFirst = false;
        return true;
    }

    return false;
}

void PairFont::SetLineFeed(int lf) {
    if (mFirst->GetHeight() >= mSecond->GetHeight()) {
        mFirst->SetLineFeed(lf);
    } else {
        mSecond->SetLineFeed(lf);
    }
}

int PairFont::GetCharWidth(u16 c) const {
    if (mFirst->HasGlyph(c)) {
        return mFirst->GetCharWidth(c);
    } else if (mSecond->HasGlyph(c)) {
        return mSecond->GetCharWidth(c);
    } else if (mAlternateWithFirst) {
        return mFirst->GetCharWidth(c);
    } else {
        return mSecond->GetCharWidth(c);
    }
}

CharWidths PairFont::GetCharWidths(u16 c) const {
    if (mFirst->HasGlyph(c)) {
        return mFirst->GetCharWidths(c);
    } else if (mSecond->HasGlyph(c)) {
        return mSecond->GetCharWidths(c);
    } else if (mAlternateWithFirst) {
        return mFirst->GetCharWidths(c);
    } else {
        return mSecond->GetCharWidths(c);
    }
}

void PairFont::GetGlyph(Glyph *out, u16 c) const {
    if (mFirst->HasGlyph(c)) {
        mFirst->GetGlyph(out, c);
    } else if (mSecond->HasGlyph(c)) {
        mSecond->GetGlyph(out, c);
    } else if (mAlternateWithFirst) {
        mFirst->GetGlyph(out, c);
    } else {
        mSecond->GetGlyph(out, c);
    }
}

bool PairFont::HasGlyph(u16 c) const {
    return mFirst->HasGlyph(c) || mSecond->HasGlyph(c);
}

FontEncoding PairFont::GetEncoding() const {
    return mFirst->GetEncoding();
}

} // namespace ut
} // namespace nw4r
