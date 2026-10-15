#ifndef SCN_STEP_GIMMICK_SWITCHRECEIVERMANAGER_H
#define SCN_STEP_GIMMICK_SWITCHRECEIVERMANAGER_H

#include "hel/common/MutableArray.h"
#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {

class Component;

namespace gimmick {

class SwitchReceiver;

class SwitchReceiverManager {
public:
    SwitchReceiverManager(Component& component);
    ~SwitchReceiverManager();

    void add(SwitchReceiver* receiver);
    void remove(SwitchReceiver* receiver);
    void onSwitchOn(u32 id);
    void onSwitchOff(u32 id);
    void onSwitchToggle(u32 id);
    void onSwitchOnFromSuperBeamSwitch(u32 id);
    hel::math::Vector2 getPos(u32 id) const;

private:
    Component& mComponent;
    hel::common::MutableArray<SwitchReceiver*, 32> mArray;
};

}}}  // namespace scn::step::gimmick

#endif
