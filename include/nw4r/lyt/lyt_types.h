#ifndef NW4R_LYT_TYPES_H
#define NW4R_LYT_TYPES_H

#include "types.h"

namespace nw4r {
namespace lyt {

struct Size {
    Size() : width(0.0f), height(0.0f) {}

    Size& operator=(const Size& other) {
        width = other.width;
        height = other.height;
        return *this;
    }

    f32 width;
    f32 height;
};

}
}

#endif
