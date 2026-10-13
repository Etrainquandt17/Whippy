#ifndef SCN_STEP_BOSS_DOUBTER_STATEWAFT_H
#define SCN_STEP_BOSS_DOUBTER_STATEWAFT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateWaft : public StateBase {
public:
    StateWaft(Boss* boss);
    virtual ~StateWaft();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 _8;
};

}}}}  // namespace scn::step::boss::doubter

#endif
