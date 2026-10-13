#ifndef SCN_STEP_CHARA_SOUNDSE_H
#define SCN_STEP_CHARA_SOUNDSE_H

#include "types.h"

namespace gobj {
class Location;
}

namespace scn {
namespace step {

class Component;

namespace chara {

// TODO: members.
class SoundSE {
public:
    SoundSE(Component& component, const gobj::Location& location);

    void start(u32 id);
    void stop();
    bool isPlaying() const;
    bool isPause() const;
    void pause();
    void unpause();
    void pauseInc();
    void pauseDec();
    void pauseReset();
    void updateVolume();
};

}}}  // namespace scn::step::chara

#endif
