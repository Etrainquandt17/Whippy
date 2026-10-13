#ifndef G3D_COLORANIMCONTEXT_H
#define G3D_COLORANIMCONTEXT_H

#include "g3d/MaterialAccessor.h"
#include "types.h"

namespace g3d {

class ColorAnimContext {
public:
    ColorAnimContext(const MaterialAccessor& material, bool useFlash);

    static bool DefaultUseFlash();

private:
    MaterialAccessor mMaterial;
    bool mUseFlash;
};

}  // namespace g3d

#endif
