#ifndef SCN_STEP_GIMMICK_AREAEVENT_MINTAREAEVENT_H
#define SCN_STEP_GIMMICK_AREAEVENT_MINTAREAEVENT_H

namespace scn {
namespace step {
namespace gimmick {
namespace areaevent {

class AreaEvent;

class MintAreaEvent {
public:
    static void Register(AreaEvent& obj);
    static void Unregister(AreaEvent& obj);
    static AreaEvent& Obj();
};

}}}}  // namespace scn::step::gimmick::areaevent

#endif
