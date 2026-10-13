#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATESUPERSWORD_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATESUPERSWORD_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateSuperSword : public IState {
public:
    StateSuperSword(Boss* boss);
    virtual ~StateSuperSword();
};

}

}}}  // namespace scn::step::boss

#endif
