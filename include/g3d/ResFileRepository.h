#ifndef G3D_RESFILEREPOSITORY_H
#define G3D_RESFILEREPOSITORY_H

#include "g3d/ResFileAccessor.h"
#include "types.h"

namespace g3d {

class ResFileRepository {
public:
    ResFileRepository();
    ~ResFileRepository();

    ResFileAccessor get(const char* path, bool);
};

}

#endif
