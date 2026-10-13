#ifndef SCN_STEP_GIMMICK_STEPMOVEINFO_H
#define SCN_STEP_GIMMICK_STEPMOVEINFO_H

#include "types.h"

namespace scn {
namespace step {
namespace gimmick {

class StepMoveInfo {
public:
    bool isEqualsMapAndScene(const StepMoveInfo& other) const;

    int _0;
    u32 _4;
    int _8;
};

}
}
}

#endif
