#ifndef SCN_STEP_GIMMICK_AREAEVENT_AREAEVENT_H
#define SCN_STEP_GIMMICK_AREAEVENT_AREAEVENT_H

#include "types.h"

namespace scn {
namespace step {
namespace gimmick {
namespace areaevent {

// TODO: no members yet; only the functions the script bindings call are declared.
class AreaEvent {
public:
    int getNextSphereUnlockDemo();
    void setEventEnd(bool isEnd);
    void setZoomSphereUnlock(int index);
    void setZoomInduction();
    void setZoom(f32, f32, f32, f32);
    void unsetZoom();
    void doorUnlock(int index);
    bool isUnlockEnd(int index);
};

}}}}  // namespace scn::step::gimmick::areaevent

#endif
