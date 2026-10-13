#ifndef SCN_STEP_CORE_G3DROOTSET_H
#define SCN_STEP_CORE_G3DROOTSET_H

#include "scn/step/core/DrawLayerKind.h"
#include "types.h"

namespace g3d {
class Root;
}

namespace scn {
namespace step {

class Component;

namespace core {

// TODO: the members; a hel::common::AutoDeleteArray<g3d::Root, 12> is at 4.
class G3DRootSet {
public:
    G3DRootSet(Component& component);
    ~G3DRootSet();

    g3d::Root& root(DrawLayerKind kind);

private:
    u32 _0[0x6C / 4];
};

}
}
}

#endif
