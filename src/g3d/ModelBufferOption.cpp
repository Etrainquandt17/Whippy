#include "g3d/ModelBufferOption.h"

namespace g3d {

ModelBufferOption::ModelBufferOption()
    : _0(false)
    , _1(false)
    , _2(false)
    , _3(false)
    , _4(false)
    , _5(false)
    , _6(false)
    , _7(false)
    , _8(false)
    , _9(false)
    , _A(false)
    , _B(false)
    , _C(false)
    , _D(false)
    , _E(false)
    , _F(false) {}

void ModelBufferOption::addAnimMatColor() {
    _3 = _8 = true;
}

void ModelBufferOption::addAnimTexPattern() {
    _1 = _0 = true;
}

void ModelBufferOption::addAnimTexSRT() {
    _2 = true;
}

void ModelBufferOption::addAnimVisible() {
    _6 = true;
}

u32 ModelBufferOption::value() const {
    u32 value = _0 | (_1 ? 0x2 : 0);
    value |= _2 ? 0x4 : 0;
    value |= _3 ? 0x8 : 0;
    value |= _4 ? 0x10 : 0;
    value |= _5 ? 0x20 : 0;
    value |= _6 ? 0x40 : 0;
    value |= _7 ? 0x80 : 0;
    value |= _8 ? 0x100 : 0;
    value |= _9 ? 0x200 : 0;
    value |= _A ? 0x400 : 0;
    value |= _B ? 0x800 : 0;
    value |= _C ? 0x1000 : 0;
    value |= _D ? 0x2000 : 0;
    value |= _E ? 0x4000 : 0;
    value |= _F ? 0x1000000 : 0;
    return value;
}

}  // namespace g3d
