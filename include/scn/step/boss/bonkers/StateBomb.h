#ifndef SCN_STEP_BOSS_BONKERS_STATEBOMB_H
#define SCN_STEP_BOSS_BONKERS_STATEBOMB_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/bonkers/StateBombStart.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

class StateBomb : public StateBase {
public:
    struct Config {
        hel::math::Vector2 _0;
        bool _8;
        bool _9;
    };

    StateBomb(Boss* boss, Config config);
    virtual ~StateBomb();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqBomb();

    Config mConfig;
};

}}}}  // namespace scn::step::boss::bonkers

#endif
