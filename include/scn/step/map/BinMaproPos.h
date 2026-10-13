#ifndef SCN_STEP_MAP_BINMAPROPOS_H
#define SCN_STEP_MAP_BINMAPROPOS_H

#include "scn/step/MaproPos.h"
#include "types.h"

namespace scn {
namespace step {
namespace map {

class BinMaproPos {
public:
    MaproPos toMaproPos() const;

private:
    u32 _0;
    u32 _4;
};

}
}
}

#endif
