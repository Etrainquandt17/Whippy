#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEGRANDCROSSNIP_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEGRANDCROSSNIP_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

class StateGrandCrossNip : public StateBase {
public:
    StateGrandCrossNip(Enemy* enemy);
    virtual ~StateGrandCrossNip();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mMoveFrame;
    hel::math::Vector2 mStart;
    hel::math::Vector2 mEnd;
};

}}}}  // namespace scn::step::enemy::landiasingle

#endif
