#ifndef SCN_STEP_HERO_HAMMER_STATETHROW_H
#define SCN_STEP_HERO_HAMMER_STATETHROW_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

class StateThrow : public StateBase {
public:
    StateThrow(Hero* hero);
    virtual ~StateThrow();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

#ifndef VERSION_SUKK01
private:
    bool mIsEnd;
#endif
};

}}}}  // namespace scn::step::hero::hammer

#endif
