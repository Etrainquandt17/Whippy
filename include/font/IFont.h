#ifndef FONT_IFONT_H
#define FONT_IFONT_H

namespace nw4r {
namespace ut {
class Font;
}
}

namespace font {

// TODO: the name of this interface is a guess; Font and PairFont share it.
class IFont {
public:
    virtual const char* name() const = 0;
    virtual void load() = 0;
    virtual void unload() = 0;
    virtual bool loaded() const = 0;
    virtual nw4r::ut::Font& font() = 0;
};

}

#endif
