#ifndef SCN_STEP_CONTEXTMODE_H
#define SCN_STEP_CONTEXTMODE_H

#include "scn/step/LevelKind.h"
#include "storage/StoryMode.h"
#include "types.h"

namespace scn {
namespace step {

class ContextMode {
public:
    static ContextMode Create();

    bool isExtraMode() const;
    bool isArenaMode() const;

    int _0;
    bool _4;
    int _8;
    storage::StoryMode _C;
    LevelKind _10;
};

}
}

#endif
