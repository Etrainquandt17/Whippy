#ifndef SCN_STEP_ENEMY_STRIKEBOXBULLET_PARAMDATA_H
#define SCN_STEP_ENEMY_STRIKEBOXBULLET_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace strikeboxbullet {

// TODO: the name is a guess: nothing in the game names what Param::strikeboxbullet() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mCollFrame[2];
    f32 mCollSize[2];
    u32 mLifeFrame;
};

}
}
}
}

#endif
