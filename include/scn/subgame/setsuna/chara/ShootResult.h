#ifndef SCN_SUBGAME_SETSUNA_CHARA_SHOOTRESULT_H
#define SCN_SUBGAME_SETSUNA_CHARA_SHOOTRESULT_H

#include "types.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace chara {

class ShootResult {
public:
    ShootResult();
    ShootResult(const ShootResult& other);

    bool isSuccess() const;

    int _0;
    u32 _4;
    f32 _8[3];
};

}
}
}
}

#endif
