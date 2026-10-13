#ifndef SCN_STEP_ENEMY_COMMON_STATEMAHOROA2CALLINGSHOTAPPEAR_H
#define SCN_STEP_ENEMY_COMMON_STATEMAHOROA2CALLINGSHOTAPPEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateMahoroa2CallingShotAppear : public StateBase {
public:
    StateMahoroa2CallingShotAppear(Enemy* enemy);
    virtual ~StateMahoroa2CallingShotAppear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::common

#endif
