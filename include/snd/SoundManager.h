#ifndef SND_SOUNDMANAGER_H
#define SND_SOUNDMANAGER_H

#include "hel/common/ExplicitSingleton.h"
#include "types.h"

namespace snd {

class BgmPlayer;

class SoundManager : public hel::common::ExplicitSingleton<SoundManager> {
public:
    SoundManager();
    ~SoundManager();

    BgmPlayer& bgm();

private:
    u32 _0[0xBB];
};

}

#endif
