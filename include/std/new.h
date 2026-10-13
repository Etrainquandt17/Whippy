#ifndef STD_NEW_H
#define STD_NEW_H

#include "types.h"

namespace std {

struct nothrow_t {};

}

inline void* operator new(u32, void* ptr) {
    return ptr;
}

#endif
