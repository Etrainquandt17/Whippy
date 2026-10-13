#ifndef SCN_WMAP_SHIP_H
#define SCN_WMAP_SHIP_H

#include "g3d/ResFileAccessor.h"
#include "g3d/StdModel.h"
#include "scn/wmap/UnlockKind.h"
#include "types.h"

namespace scn {
namespace wmap {

class Component;

class Ship {
public:
    Ship(Component& component);

    void procFixPos();

private:
    Component& mComponent;
    g3d::ResFileAccessor mResFile;
    g3d::StdModel mModel;
    UnlockKind mUnlockKind;
};

}
}

#endif
