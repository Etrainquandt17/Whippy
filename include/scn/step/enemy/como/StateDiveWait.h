#ifndef SCN_STEP_ENEMY_COMO_STATEDIVEWAIT_H
#define SCN_STEP_ENEMY_COMO_STATEDIVEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

class StateDiveWait : public StateBase {
public:
    StateDiveWait(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::como

#endif
