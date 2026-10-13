#include "scn/step/gimmick/areaevent/MintAreaEvent.h"

#include "hel/common/PointerWrapper.h"

namespace scn {
namespace step {
namespace gimmick {
namespace areaevent {

namespace {

hel::common::PointerWrapper<AreaEvent> t_obj;

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

}
}
}
}
