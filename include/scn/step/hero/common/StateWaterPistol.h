#ifndef SCN_STEP_HERO_COMMON_STATEWATERPISTOL_H
#define SCN_STEP_HERO_COMMON_STATEWATERPISTOL_H

#include "hel/math/Vector2.h"
#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateWaterPistol : public StateBase {
public:
    static bool TryToChangeState(Hero* hero, const hel::math::Vector2& dir);
    static bool TryToChangeState(Hero* hero);

    StateWaterPistol(Hero* hero, const hel::math::Vector2& dir);
    virtual ~StateWaterPistol();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector2 mDir;
};

}}}}  // namespace scn::step::hero::common

#endif
