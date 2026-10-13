#ifndef HEL_COMMON_COLOR_H
#define HEL_COMMON_COLOR_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace hel {
namespace common {

class Color {
public:
    static const Color BLACK;
    static const Color GRAY;
    static const Color WHITE;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
    static const Color MAGENTA;
    static const Color CYAN;

    Color() : r(0), g(0), b(0), a(0) {}
    Color(u8 r, u8 g, u8 b, u8 a);

    // TODO: inferred. A Color given to a const GXColor& parameter is copied to a
    // temporary as one word.
    operator GXColor() const { return *reinterpret_cast<const GXColor*>(this); }

    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

inline Color::Color(u8 r, u8 g, u8 b, u8 a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

}}  // namespace hel::common

#endif
