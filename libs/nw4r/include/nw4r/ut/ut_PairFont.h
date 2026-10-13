#ifndef NW4R_UT_PAIR_FONT_H
#define NW4R_UT_PAIR_FONT_H
#include "nw4r/types_nw4r.h"
#include "nw4r/ut/ut_Font.h"

namespace nw4r {
namespace ut {

class PairFont : public Font {
public:
    PairFont(Font *pFirst, Font *pSecond);
    virtual ~PairFont(); // at 0x8

    virtual int GetWidth() const;                                // at 0xC
    virtual int GetHeight() const;                               // at 0x10
    virtual int GetAscent() const;                               // at 0x14
    virtual int GetDescent() const;                              // at 0x18
    virtual int GetBaselinePos() const;                          // at 0x1C
    virtual int GetCellHeight() const;                           // at 0x20
    virtual int GetCellWidth() const;                            // at 0x24
    virtual int GetMaxCharWidth() const;                         // at 0x28
    virtual Type GetType() const;                                // at 0x2C
    virtual GXTexFmt GetTextureFormat() const;                   // at 0x30
    virtual int GetLineFeed() const;                             // at 0x34
    virtual CharWidths GetDefaultCharWidths() const;             // at 0x38
    virtual void SetDefaultCharWidths(const CharWidths &widths); // at 0x3C
    virtual bool SetAlternateChar(u16 c);                        // at 0x40
    virtual void SetLineFeed(int lf);                            // at 0x44
    virtual int GetCharWidth(u16 c) const;                       // at 0x48
    virtual CharWidths GetCharWidths(u16 c) const;               // at 0x4C
    virtual void GetGlyph(Glyph *out, u16 c) const;              // at 0x50
    virtual bool HasGlyph(u16 c) const;                          // at 0x54
    virtual FontEncoding GetEncoding() const;                    // at 0x58

private:
    Font *mFirst;             // at 0x10
    Font *mSecond;            // at 0x14
    bool mAlternateWithFirst; // at 0x18
};

} // namespace ut
} // namespace nw4r

#endif
