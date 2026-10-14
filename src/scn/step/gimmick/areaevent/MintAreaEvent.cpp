#include "scn/step/gimmick/areaevent/MintAreaEvent.h"

#include "hel/common/PointerWrapper.h"

using hel::common::PointerWrapper;

namespace scn {
namespace step {
namespace gimmick {
namespace areaevent {

namespace {

PointerWrapper<AreaEvent> t_obj;

}

void MintAreaEvent::Register(AreaEvent& obj) {
    t_obj.set(obj);
}

void MintAreaEvent::Unregister(AreaEvent&) {
    t_obj.reset();
}

AreaEvent& MintAreaEvent::Obj() {
    return t_obj.ref();
}

}}}}  // namespace scn::step::gimmick::areaevent
