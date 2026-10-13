#ifndef PAUSE_CONTEXTINIT_H
#define PAUSE_CONTEXTINIT_H

#include "pause/ModeKind.h"
#include "pause/SpecialKind.h"
#include "storage/StoryMode.h"
#include "types.h"

namespace pause {

class ContextInit {
public:
    storage::StoryMode storyMode() const;
    ModeKind modeKind() const;
    SpecialKind specialKind() const;

private:
    u32 _0[0x3];
};

}

#endif
