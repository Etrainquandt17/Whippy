#ifndef SCN_GOALGAME_HEROCTRL_H
#define SCN_GOALGAME_HEROCTRL_H

#include "types.h"

namespace scn {
namespace goalgame {

class HeroCtrl {
public:
    ~HeroCtrl();

private:
    u32 _0[0xD0AC / 4];
};

}
}

#endif
