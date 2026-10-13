#ifndef SCN_STEP_BOSS_HRD3_STATEBEAMFAR_H
#define SCN_STEP_BOSS_HRD3_STATEBEAMFAR_H

#include "scn/step/boss/IState.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace hrd3 {

// TODO: members.
class StateBeamFar : public IState {
public:
    StateBeamFar(Boss* boss);
    virtual ~StateBeamFar();
};

}}}}  // namespace scn::step::boss::hrd3

#endif
