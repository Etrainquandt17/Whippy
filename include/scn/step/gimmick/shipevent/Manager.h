#ifndef SCN_STEP_GIMMICK_SHIPEVENT_MANAGER_H
#define SCN_STEP_GIMMICK_SHIPEVENT_MANAGER_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {

class Component;

namespace gimmick {
namespace shipevent {

// TODO: members, and the functions whose return types are not known yet (getTalkPos, getPlayerRequester).
class Manager {
public:
    Manager(Component& component);
    ~Manager();

    void updateFrame();
    bool isCapture(const hel::math::Vector2& pos);
    void talkStart(bool);
    void setIsClearDemo(bool isClearDemo);
    bool isClearDemo();
    void setSeat(u32 index);
    bool isSeat(u32 index) const;
};

}
}
}
}

#endif
