#ifndef SCN_STEP_HERO_STONE_STATEFALLSCREWSTART_H
#define SCN_STEP_HERO_STONE_STATEFALLSCREWSTART_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

class Context;

class StateFallScrewStart : public StateBase {
public:
    StateFallScrewStart(Hero* hero, Context& context);
    virtual ~StateFallScrewStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    Context& mContext;
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::stone

#endif
