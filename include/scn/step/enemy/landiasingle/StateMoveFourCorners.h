#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEMOVEFOURCORNERS_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEMOVEFOURCORNERS_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

class StateMoveFourCorners : public StateBase {
public:
    struct Config {
        bool _0;
        f32 _4;
    };

    StateMoveFourCorners(Enemy* enemy, Config config);
    virtual ~StateMoveFourCorners();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    hel::math::Vector2 mStart;
    hel::math::Vector2 mEnd;
    Config mConfig;
};

}}}}  // namespace scn::step::enemy::landiasingle

#endif
