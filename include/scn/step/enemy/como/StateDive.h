#ifndef SCN_STEP_ENEMY_COMO_STATEDIVE_H
#define SCN_STEP_ENEMY_COMO_STATEDIVE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

class StateDive : public StateBase {
public:
    StateDive(Enemy* enemy);
    virtual ~StateDive();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    f32 mSpeed;
};

}}}}  // namespace scn::step::enemy::como

#endif
