#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATESUMMONLOWPER_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATESUMMONLOWPER_H

#include "scn/step/boss/IState.h"
#include "scn/step/boss/mahoroabattle1/LowperType.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateSummonLowper : public IState {
public:
    StateSummonLowper(Boss* boss, LowperType type, u32 _2, u32 _3);
    virtual ~StateSummonLowper();
};

}}}}  // namespace scn::step::boss::mahoroabattle1

#endif
