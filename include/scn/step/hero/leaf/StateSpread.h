#ifndef SCN_STEP_HERO_LEAF_STATESPREAD_H
#define SCN_STEP_HERO_LEAF_STATESPREAD_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

class StateSpread : public StateBase {
public:
    StateSpread(Hero* hero);
    virtual ~StateSpread();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsEnd;
};

}}}}  // namespace scn::step::hero::leaf

#endif
