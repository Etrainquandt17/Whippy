#ifndef SCN_STEP_STAGEKINDUTIL_H
#define SCN_STEP_STAGEKINDUTIL_H

#include "scn/step/LevelKind.h"
#include "scn/step/StageKind.h"
#include "types.h"

namespace scn {
namespace step {

class StageKindUtil {
public:
    static u32 SphereTotalNum();
    static u32 SphereTotalNum(StageKind stage);
    static u32 SphereTotalNum(LevelKind level);
    static bool IsBossStage(StageKind stage);
    static bool IsFinalStage(StageKind stage);
    static LevelKind BelongLevelKind(StageKind stage);
    static u32 StageCount(LevelKind level);
};

}
}

#endif
