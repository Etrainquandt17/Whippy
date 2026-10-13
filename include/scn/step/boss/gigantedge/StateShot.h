#ifndef SCN_STEP_BOSS_GIGANTEDGE_STATESHOT_H
#define SCN_STEP_BOSS_GIGANTEDGE_STATESHOT_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace gigantedge {

class StateShot : public StateBase {
public:
    struct Config {
        bool _0;
    };

    StateShot(Boss* boss, Config config);
    virtual ~StateShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    Config mConfig;
};

}}}}  // namespace scn::step::boss::gigantedge

#endif
