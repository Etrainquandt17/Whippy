#ifndef SCN_STEP_ENEMY_WADDLEDEE_STATESMASHED_H
#define SCN_STEP_ENEMY_WADDLEDEE_STATESMASHED_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

class StateSmashed : public StateBase {
public:
    StateSmashed(Enemy* enemy);
    virtual ~StateSmashed();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
    f32 mRotH;
    bool mIsLanded;
};

}}}}  // namespace scn::step::enemy::waddledee

#endif
