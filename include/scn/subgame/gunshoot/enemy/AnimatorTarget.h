#ifndef SCN_SUBGAME_GUNSHOOT_ENEMY_ANIMATORTARGET_H
#define SCN_SUBGAME_GUNSHOOT_ENEMY_ANIMATORTARGET_H

#include "hel/common/PointerWrapper.h"
#include "scn/subgame/common/view/ModelAccessor.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace enemy {

struct AnimatorTarget {
    ~AnimatorTarget() {}

    common::view::ModelAccessor* _0;
    hel::common::PointerWrapper<common::view::ModelAccessor> _4;
    hel::common::PointerWrapper<common::view::ModelAccessor> _8;
    u32 _C;
};

}
}
}
}

#endif
