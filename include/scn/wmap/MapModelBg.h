#ifndef SCN_WMAP_MAPMODELBG_H
#define SCN_WMAP_MAPMODELBG_H

#include "hel/math/Matrix34.h"

namespace scn {
namespace wmap {

// TODO: only what scn/wmap/Ship.cpp calls. The class's members aren't known yet.
class MapModelBg {
public:
    hel::math::Matrix34 getShipMtx();
};

}
}

#endif
