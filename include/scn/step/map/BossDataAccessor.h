#ifndef SCN_STEP_MAP_BOSSDATAACCESSOR_H
#define SCN_STEP_MAP_BOSSDATAACCESSOR_H

#include "scn/step/map/BinBossKind.h"
#include "scn/step/map/BinBossVariation.h"
#include "scn/step/map/BinMaproPos.h"
#include "types.h"

namespace scn {
namespace step {
namespace map {

// TODO: the size and the members past the position.
struct BinBossEntry {
    BinBossKind _0;
    BinBossVariation _4;
    u32 _8;
    u32 _c;
    u32 _10;
    BinMaproPos _14;
};

class BossDataAccessor {
public:
    u32 count() const;
    const BinBossEntry& at(u32 index) const;

private:
    u32 _0;
};

}
}
}

#endif
