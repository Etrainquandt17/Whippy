#ifndef SCN_STEP_HERO_HIGHJUMP_STATEROCKETFALLEND_H
#define SCN_STEP_HERO_HIGHJUMP_STATEROCKETFALLEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

class StateRocketFallEnd : public StateBase {
public:
    StateRocketFallEnd(Hero* hero);
    virtual ~StateRocketFallEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
};

}}}}  // namespace scn::step::hero::highjump

#endif
