#ifndef SCN_STEP_HERO_COMMON_STATEDEMOFALL_H
#define SCN_STEP_HERO_COMMON_STATEDEMOFALL_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateDemoFall : public StateBase {
public:
    StateDemoFall(Hero* hero);
    virtual ~StateDemoFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool canPlancher();

    u32 mFrame;
};

}}}}  // namespace scn::step::hero::common

#endif
