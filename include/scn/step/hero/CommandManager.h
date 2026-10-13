#ifndef SCN_STEP_HERO_COMMANDMANAGER_H
#define SCN_STEP_HERO_COMMANDMANAGER_H

#include "scn/step/hero/ButtonMask.h"

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class CommandManager {
public:
    void setWait(ButtonMask mask);
    u32 getHoldFrame(ButtonMask mask) const;
    void resetHoldFrame(ButtonMask mask);
    u32 getTriggerPastFrame(ButtonMask mask) const;
};

}}}  // namespace scn::step::hero

#endif
