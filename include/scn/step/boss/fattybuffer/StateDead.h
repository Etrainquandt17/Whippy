#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATEDEAD_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATEDEAD_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

// TODO: members and the overrides.
class StateDead : public StateBase {
public:
    StateDead(Boss* boss);
    virtual ~StateDead();
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
