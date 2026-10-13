#ifndef SCN_STEP_ENEMY_POPPYBROJR_STATETHROW_H
#define SCN_STEP_ENEMY_POPPYBROJR_STATETHROW_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace poppybrojr {

class StateThrow : public StateBase {
public:
    StateThrow(Enemy* enemy);
    virtual ~StateThrow();
    virtual void procAnim();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mThrowFrame;
};

}}}}  // namespace scn::step::enemy::poppybrojr

#endif
