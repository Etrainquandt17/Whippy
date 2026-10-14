#include "scn/step/gimmick/lvmapdoor/MintLvMapDoor.h"

#include "hel/common/PointerWrapper.h"

using hel::common::PointerWrapper;

namespace scn {
namespace step {
namespace gimmick {
namespace lvmapdoor {

namespace {

PointerWrapper<LvMapDoor> t_obj;

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

}}}}  // namespace scn::step::gimmick::lvmapdoor
