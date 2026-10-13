#ifndef SCN_STEP_BOSS_MAHOROAROAH_BODYEFFECTCTRL_H
#define SCN_STEP_BOSS_MAHOROAROAH_BODYEFFECTCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

}
class Boss;
namespace mahoroaroah {

class BodyEffectCtrl {
public:
    BodyEffectCtrl(Boss& boss);
    ~BodyEffectCtrl();

    void setVisible(bool isWarp);
    void setInvisible();
    void reqAfterImage();
    void releaseAfterImage();

private:
    Boss& mBoss;
    bool mIsVisible;
};

}}}}  // namespace scn::step::boss::mahoroaroah

#endif
