#ifndef SCN_STEP_ENEMY_COMMON_STATESHOOTINGCOMEINZ_H
#define SCN_STEP_ENEMY_COMMON_STATESHOOTINGCOMEINZ_H

#include "scn/step/enemy/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace common {

// TODO: members.
class StateShootingComeInZ : public IState {
public:
    struct Config {
        bool _0;
        bool _1;
    };

    StateShootingComeInZ(Enemy* enemy, Config config);
    virtual ~StateShootingComeInZ();
};

}}}}  // namespace scn::step::enemy::common

#endif
