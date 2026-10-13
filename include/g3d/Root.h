#ifndef G3D_ROOT_H
#define G3D_ROOT_H

#include "types.h"

namespace g3d {

class CameraAccessor;
class FogAccessor;
class RootContext;

class Root {
public:
    Root(const RootContext& context);
    ~Root();

    CameraAccessor currentCamera() const;
    FogAccessor fog() const;

private:
    u32 _0[0x14];
};

}

#endif
