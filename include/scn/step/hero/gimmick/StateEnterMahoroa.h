#ifndef SCN_STEP_HERO_GIMMICK_STATEENTERMAHOROA_H
#define SCN_STEP_HERO_GIMMICK_STATEENTERMAHOROA_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace gimmick {

// TODO: only what the common states call.
class StateEnterMahoroa : public StateBase {
public:
    static bool TryToChangeState(Hero* hero, bool);

    StateEnterMahoroa(Hero* hero);
};

}}}}  // namespace scn::step::hero::gimmick

#endif
