#ifndef SCN_STEP_BOSS_LANDIA_STATEZGLIDE_H
#define SCN_STEP_BOSS_LANDIA_STATEZGLIDE_H

#include "scn/step/boss/IState.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace landia {

// TODO: members.
class StateZGlide : public IState {
public:
    StateZGlide(Boss* boss);
    virtual ~StateZGlide();
};

}}}}  // namespace scn::step::boss::landia

#endif
