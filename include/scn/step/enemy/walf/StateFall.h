#ifndef SCN_STEP_ENEMY_WALF_STATEFALL_H
#define SCN_STEP_ENEMY_WALF_STATEFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace walf {

class StateFall : public StateBase {
public:
    StateFall(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::walf

#endif
