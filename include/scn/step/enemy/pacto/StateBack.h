#ifndef SCN_STEP_ENEMY_PACTO_STATEBACK_H
#define SCN_STEP_ENEMY_PACTO_STATEBACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace pacto {

class StateBack : public StateBase {
public:
    StateBack(Enemy* enemy);
    virtual void procMove();

private:
    int mFrame;
    int mTotalFrame;
    f32 mDist;
};

}}}}  // namespace scn::step::enemy::pacto

#endif
