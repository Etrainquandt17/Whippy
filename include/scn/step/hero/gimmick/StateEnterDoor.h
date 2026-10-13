#ifndef SCN_STEP_HERO_GIMMICK_STATEENTERDOOR_H
#define SCN_STEP_HERO_GIMMICK_STATEENTERDOOR_H

#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace gimmick {

// TODO: only what the common states call.
class StateEnterDoor : public StateBase {
public:
    static bool TryToChangeState(Hero* hero, bool);
    static bool TryToChangeState(Hero* hero, ScriptKind script, bool);
};

}}}}  // namespace scn::step::hero::gimmick

#endif
