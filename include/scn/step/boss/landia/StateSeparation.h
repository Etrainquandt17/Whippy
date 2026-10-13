#ifndef SCN_STEP_BOSS_LANDIA_STATESEPARATION_H
#define SCN_STEP_BOSS_LANDIA_STATESEPARATION_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateSeparation : public StateBase {
public:
    StateSeparation(Boss* boss);
    virtual ~StateSeparation();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::landia

#endif
