#ifndef SCN_STEP_MAP_KINDUTIL_H
#define SCN_STEP_MAP_KINDUTIL_H

#include "scn/step/LevelKind.h"
#include "scn/step/StageKind.h"
#include "scn/step/map/Kind.h"
#include "storage/StoryMode.h"
#include "types.h"

namespace file {
class DNOption;
}

namespace scn {
namespace step {
namespace map {

class KindUtil {
public:
    static bool IsStageMap(Kind kind);
    static bool IsFinalStageMap(Kind kind);
    static bool IsLevelMap(Kind kind);
    static StageKind ToStageKind(Kind kind);
    static u32 ToStageIndex(Kind kind);
    static u32 ToStageIndex(StageKind stage);
    static void PreLoadRequest(Kind kind, const file::DNOption& option);
    static Kind GoToShipInStage(storage::StoryMode mode, bool);
    static Kind ToKind(LevelKind level, u32 index);
    static u32 ToLevelIndex(Kind kind);
    static bool IsFinalBattle(Kind kind);
};

}
}
}

#endif
