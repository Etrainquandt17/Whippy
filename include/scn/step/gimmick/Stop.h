#ifndef SCN_STEP_GIMMICK_STOP_H
#define SCN_STEP_GIMMICK_STOP_H

#include "types.h"

namespace snd {
class SERequestor;
}

namespace scn {
namespace step {

class Component;

namespace gimmick {

class Effect;

class Stop {
public:
    Stop(Component& component);
    ~Stop();

    bool isSuperStopped() const;
    bool isSuperActionTime() const;
    bool isSkipObjCollReact() const;
    bool isObjStopped() const;
    void onObjCollReactHit();
    void setSpecial();
    void unsetSpecial();
    void add(Effect& effect);
    void addSuper(Effect& effect);
    void add(snd::SERequestor& requestor);
    void remove(Effect& effect);
    void removeSuper(Effect& effect);
    void remove(snd::SERequestor& requestor);

private:
    u8 _0[0x68];
};

}}}  // namespace scn::step::gimmick

#endif
