#ifndef MOV_MOVIEKINDUTIL_H
#define MOV_MOVIEKINDUTIL_H

#include "mov/MovieKind.h"
#include "revolution/gx/GXStruct.h"

namespace mov {

class MovieKindUtil {
public:
    static GXColor PreFadeColor(MovieKind kind);
};

}

#endif
