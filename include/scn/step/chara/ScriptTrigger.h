#ifndef SCN_STEP_CHARA_SCRIPTTRIGGER_H
#define SCN_STEP_CHARA_SCRIPTTRIGGER_H

#include "types.h"

namespace scn {
namespace step {
namespace chara {

// TODO: the members are unknown.
class ScriptTrigger {
public:
    void set(u32 trigger);
    bool get(u32 trigger);
    void clear();
};

}}}  // namespace scn::step::chara

#endif
