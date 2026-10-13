#ifndef SCN_STEP_GIMMICK_POPFLOWER_ITEMGEN_H
#define SCN_STEP_GIMMICK_POPFLOWER_ITEMGEN_H

#include "hel/math/Vector2.h"
#include "scn/step/gimmick/ParamAccessor.h"
#include "scn/step/gimmick/popflower/Param.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {

class Component;

namespace hero {
class Hero;
}

namespace gimmick {
namespace popflower {

// TODO: members unknown; only what scn/step/gimmick/popflower/PopFlower.cpp calls is declared.
class ItemGen {
public:
    ItemGen(Component& component, ParamAccessor<Param>& param);
    ~ItemGen();

    void generateItem(const hel::math::Vector2& pos, bool, const util::ObjRefHandle<hero::Hero>& hero);
};

}
}
}
}

#endif
