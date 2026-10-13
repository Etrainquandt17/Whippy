#ifndef SCN_SUBGAME_COMMON_VIEW_STAGE_H
#define SCN_SUBGAME_COMMON_VIEW_STAGE_H

#include "g3d/CameraAccessor.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace view {

class Stage {
public:
    g3d::CameraAccessor currentCamera() const;
};

}
}
}
}

#endif
