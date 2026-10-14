#ifndef SCN_STEP_CARRYITEM_STEPSHOE_SCRIPTKIND_H
#define SCN_STEP_CARRYITEM_STEPSHOE_SCRIPTKIND_H

namespace scn {
namespace step {
namespace carryitem {
namespace stepshoe {

enum ScriptKind {
    SCRIPT_KIND_JUMP_LOW_START,
    SCRIPT_KIND_JUMP_LOW,
    SCRIPT_KIND_JUMP_LOW_END,
    SCRIPT_KIND_JUMP_HIGHT_START,  // sic
    SCRIPT_KIND_JUMP_HIGH,
    SCRIPT_KIND_JUMP_HIGHT_FALL,  // sic
    SCRIPT_KIND_JUMP_HIGHT_LANDING,  // sic
    SCRIPT_KIND_FALL_HIT,
    SCRIPT_KIND_ENPTY_WAIT,  // sic
};

}}}}  // namespace scn::step::carryitem::stepshoe

#endif
