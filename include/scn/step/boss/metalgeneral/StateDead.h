#ifndef SCN_STEP_BOSS_METALGENERAL_STATEDEAD_H
#define SCN_STEP_BOSS_METALGENERAL_STATEDEAD_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateDead : public StateBase {
public:
    StateDead(Boss* boss);
    virtual ~StateDead();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void stagingBossDead();
    void setCameraZoom();

    bool mIsEnd;
    bool mIsPanelShown;
    bool mIsStaged;
    u32 mFrame;
    u32 mZoomHandle;
    u32 _14;
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
