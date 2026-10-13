#ifndef SCN_STEP_BOSS_LANDIA_STATETWINBREATH_H
#define SCN_STEP_BOSS_LANDIA_STATETWINBREATH_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace landia {

// TODO: members.
class StateTwinBreath : public IState {
public:
    struct Config {
        int _0;
    };

    StateTwinBreath(Boss* boss, Config config);
    virtual ~StateTwinBreath();
};

}}}}  // namespace scn::step::boss::landia

#endif
