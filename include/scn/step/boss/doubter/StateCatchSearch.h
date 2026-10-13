#ifndef SCN_STEP_BOSS_DOUBTER_STATECATCHSEARCH_H
#define SCN_STEP_BOSS_DOUBTER_STATECATCHSEARCH_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateCatchSearch : public StateBase {
public:
    StateCatchSearch(Boss* boss, u32 frame, u32 endFrame);
    virtual ~StateCatchSearch();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    u32 mCount;
    u32 mEndCount;
    f32 mDecel;
    bool mIsCheckCapture;
};

}
}
}
}

#endif
