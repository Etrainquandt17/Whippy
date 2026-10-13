#ifndef SCN_STEP_ENEMY_GLUNK_STATESHOT_H
#define SCN_STEP_ENEMY_GLUNK_STATESHOT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace glunk {

class StateShot : public StateBase {
public:
    StateShot(Enemy* enemy);
    virtual ~StateShot();
    virtual void procAnim();
    virtual void procFixPos();

private:
    void shot();
    
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::glunk

#endif
