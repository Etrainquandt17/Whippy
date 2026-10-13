#ifndef SCN_STEP_ENEMY_KABU_STATEFALL_H
#define SCN_STEP_ENEMY_KABU_STATEFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

class StateFall : public StateBase {
public:
    StateFall(Enemy* enemy);
    virtual ~StateFall();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mSpeed;
};

}}}}  // namespace scn::step::enemy::kabu

#endif
