#ifndef SCN_GOALGAME_UFO_H
#define SCN_GOALGAME_UFO_H

#include "scn/goalgame/GGUfoState.h"
#include "types.h"

namespace scn {
namespace goalgame {

class Ufo {
public:
    ~Ufo();

    void setState(GGUfoState state);
    GGUfoState getState();

private:
    u8 _0[0x388];
};

}
}

#endif
