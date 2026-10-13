#ifndef SCN_STEP_INFO_HEROPANEL_H
#define SCN_STEP_INFO_HEROPANEL_H

#include "types.h"

namespace scn {
namespace step {
namespace info {

class HeroPanel {
public:
    void spGaugeSetRate(f32 rate);
    void spGaugeFadeIn();
    void spGaugeFadeOut();
    void sphereCompleteLockPos();
    void sphereCompleteStart();
};

}
}
}

#endif
