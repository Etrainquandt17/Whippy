#include "scn/step/gimmick/lvmapdoor/MintLvMapDoor.h"

#include "hel/common/PointerWrapper.h"

namespace scn {
namespace step {
namespace gimmick {
namespace lvmapdoor {

namespace {

hel::common::PointerWrapper<LvMapDoor> t_obj;

}

void MintLvMapDoor::Register(LvMapDoor& obj) {
    t_obj.set(obj);
}

void MintLvMapDoor::Unregister(LvMapDoor&) {
    t_obj.reset();
}

LvMapDoor& MintLvMapDoor::Obj() {
    return t_obj.ref();
}

}
}
}
}
