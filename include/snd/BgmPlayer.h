#ifndef SND_BGMPLAYER_H
#define SND_BGMPLAYER_H

#include "types.h"

namespace snd {

class BgmPlayer {
public:
    void start(u32 id);
    void startWithSamplePos(u32 id, u32 samplePos);
    void stop();
    void stop(int fadeFrame);
    void setVolume(f32 volume);
};

}  // namespace snd

#endif
