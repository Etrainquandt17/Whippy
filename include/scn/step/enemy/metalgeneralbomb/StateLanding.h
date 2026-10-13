#ifndef SCN_STEP_ENEMY_METALGENERALBOMB_STATELANDING_H
#define SCN_STEP_ENEMY_METALGENERALBOMB_STATELANDING_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace metalgeneralbomb {

class StateLanding : public StateBase {
public:
    StateLanding(Enemy* enemy, bool isFloor);
    virtual ~StateLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsFloor;
};

}}}}  // namespace scn::step::enemy::metalgeneralbomb

#endif
