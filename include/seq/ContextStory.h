#ifndef SEQ_CONTEXTSTORY_H
#define SEQ_CONTEXTSTORY_H

#include "scn/step/ContextHero.h"
#include "storage/StoryMode.h"
#include "types.h"

namespace seq {

class ContextStory {
public:
    storage::StoryMode mStoryMode;
    u32 _4[0xD6];
    scn::step::ContextHero mHero;
    u32 _470[0x4];
};

}

#endif
