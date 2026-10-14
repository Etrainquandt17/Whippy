#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATEDEAD_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATEDEAD_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateDead : public StateBase {
public:
    StateDead(Boss* boss);
    virtual ~StateDead();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void stagingBossDead();

    bool mIsEnd;
    bool mIsPanelShown;
    bool mIsStaged;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
