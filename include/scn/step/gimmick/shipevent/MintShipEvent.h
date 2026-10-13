#ifndef SCN_STEP_GIMMICK_SHIPEVENT_MINTSHIPEVENT_H
#define SCN_STEP_GIMMICK_SHIPEVENT_MINTSHIPEVENT_H

namespace scn {
namespace step {
namespace gimmick {
namespace shipevent {

class ShipEvent;

class MintShipEvent {
public:
    static void Register(ShipEvent& obj);
    static void Unregister(ShipEvent& obj);
    static ShipEvent& Obj();
};

}
}
}
}

#endif
