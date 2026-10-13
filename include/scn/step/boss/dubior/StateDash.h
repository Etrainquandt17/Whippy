#ifndef SCN_STEP_BOSS_DUBIOR_STATEDASH_H
#define SCN_STEP_BOSS_DUBIOR_STATEDASH_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

class StateDash : public StateBase {
public:
    StateDash(Boss* boss);
    virtual ~StateDash();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsDash;
};

}}}}  // namespace scn::step::boss::dubior

#endif
