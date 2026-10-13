#ifndef SCN_STEP_ENEMY_COMO_STATECUTFALL_H
#define SCN_STEP_ENEMY_COMO_STATECUTFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

class StateCutFall : public StateBase {
public:
    StateCutFall(Enemy* enemy);
    virtual ~StateCutFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 _8;
};

}}}}  // namespace scn::step::enemy::como

#endif
