#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATEAPPEAR_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATEAPPEAR_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

// TODO: members and the overrides.
class StateAppear : public StateBase {
public:
    StateAppear(Boss* boss);
    virtual ~StateAppear();
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
