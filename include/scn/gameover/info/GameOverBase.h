#ifndef SCN_GAMEOVER_INFO_GAMEOVERBASE_H
#define SCN_GAMEOVER_INFO_GAMEOVERBASE_H

#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace gameover {
namespace info {

class GameOverBase {
public:
    f32 cursorPos() const;

private:
    u8 _0[0x8];
    int mState;
    u8 _C[0x7DC - 0xC];
    util::FrameCounter _7DC;
    u8 _7E4[0x4];
    int _7E8;
};

}
}
}

#endif
