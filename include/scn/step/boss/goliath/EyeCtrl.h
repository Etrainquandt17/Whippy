#ifndef SCN_STEP_BOSS_GOLIATH_EYECTRL_H
#define SCN_STEP_BOSS_GOLIATH_EYECTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

}
class Boss;
namespace goliath {

class EyeCtrl {
public:
    EyeCtrl(Boss& boss);

    void update();
    void setAngry(bool isAngry);
    void setKeepOpen();
    void startAnim();

private:
    void setFrame();
    void setSubAnim();

    Boss& mBoss;
    bool mIsAngry;
    bool mIsOpen;
    bool mIsAnim;
    u32 mFrame;
    u32 mOpenIndex;
};

}}}}  // namespace scn::step::boss::goliath

#endif
