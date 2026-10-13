#ifndef SCN_STEP_HERO_STONE_STATELANDING_H
#define SCN_STEP_HERO_STONE_STATELANDING_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

class Context;

class StateLanding : public StateBase {
public:
    StateLanding(Hero* hero, Context& context);
    virtual ~StateLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    Context& mContext;
    u32 mFrame;
    bool mIsCancel;
};

}}}}  // namespace scn::step::hero::stone

#endif
