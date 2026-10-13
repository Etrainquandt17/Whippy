#ifndef SND_SYSTEMSEREQUESTOR_H
#define SND_SYSTEMSEREQUESTOR_H

#include "types.h"

namespace snd {

class SystemSERequestor {
public:
    SystemSERequestor();
    ~SystemSERequestor();

    void start(u32 id);
    void stop();
    bool isPlaying() const;
    void setVolume(f32 volume);
    void setOutputMain(bool enable);
    void setOutputWR(u32 index, bool enable);

private:
    u32 _0[0x74 / 4];
};

}

#endif
