#ifndef SCN_STEP_MAP_DATAACCESSOR_H
#define SCN_STEP_MAP_DATAACCESSOR_H

#include "types.h"

namespace scn {
namespace step {
namespace map {

class GimmickDataAccessor;
class BossDataAccessor;

class DataAccessor {
public:
    bool isEnableSFXMonotone() const;
    GimmickDataAccessor gimmickDataAccessor() const;
    BossDataAccessor bossDataAccessor() const;
    u32 bgmSoundId() const;

private:
    u32 _0;
};

}
}
}

#endif
