#ifndef SND_SEREQUESTOR_H
#define SND_SEREQUESTOR_H

#include "types.h"

namespace snd {

class SERequestor {
public:
    SERequestor();
    ~SERequestor();

    void start(u32 id);
    void stop();
    bool isPlaying() const;
    bool isPause() const;
    void pause();
    void unpause();
    void pauseInc();
    void pauseDec();
    void pauseReset();
    f32 volume() const;
    void setVolume(f32 volume);
    void setPan(f32 pan);
    void setOutputMain(bool enable);
    void setOutputWR(u32 index, bool enable);
    void updateOutput();

private:
    u32 _0;
    u8 _4[0x70];
};

}

#endif
