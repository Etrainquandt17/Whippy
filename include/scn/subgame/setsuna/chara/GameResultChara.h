#ifndef SCN_SUBGAME_SETSUNA_CHARA_GAMERESULTCHARA_H
#define SCN_SUBGAME_SETSUNA_CHARA_GAMERESULTCHARA_H

#include "g3d/ModelAnimAccessor.h"
#include "hel/common/MutableArray.h"
#include "hel/common/ScopedPtr.h"
#include "hel/math/Vector3.h"
#include "scn/subgame/common/effect/Requestor.h"
#include "scn/subgame/common/view/ModelAccessor.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace chara {

class GameResultChara {
public:
    void startWait();
    void reset();
    void setMyCharaVisibility(bool visible);

private:
    u8 _0[0x8];
    u32 _8;
    u8 _C[0x40];
    int _4C;
    bool _50;
    u8 _51[0x3B];
    hel::common::MutableArray<common::view::ModelAccessor, 15> _8C;
    hel::common::MutableArray<g3d::ModelAnimAccessor, 15> _1F8;
    hel::common::MutableArray<g3d::ModelAnimAccessor, 15> _274;
    u8 _2F0[0x40];
    bool _330;
    hel::common::MutableArray<bool, 15> _334;
    int _348;
    u8 _34C[0x4];
    hel::common::ScopedPtr<common::effect::Requestor> _350;
    u8 _354[0x4];
    common::view::ModelAccessor _358;
    u8 _370[0x18];
    g3d::ModelAnimAccessor _388;
    common::view::ModelAccessor _390;
    common::view::ModelAccessor _3A8;
    u8 _3C0[0x18];
    hel::math::Vector3 _3D8;
};

}
}
}
}

#endif
