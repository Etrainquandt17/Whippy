#include "scn/step/gimmick/shipevent/MintShipEvent.h"

#include "hel/common/PointerWrapper.h"

namespace scn {
namespace step {
namespace gimmick {
namespace shipevent {

namespace {

hel::common::PointerWrapper<ShipEvent> t_obj;

}

void MintShipEvent::Register(ShipEvent& obj) {
    t_obj.set(obj);
}

void MintShipEvent::Unregister(ShipEvent&) {
    t_obj.reset();
}

ShipEvent& MintShipEvent::Obj() {
    return t_obj.ref();
}

}
}
}
}
