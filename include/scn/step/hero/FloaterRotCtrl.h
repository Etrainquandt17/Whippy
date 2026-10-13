#ifndef SCN_STEP_HERO_FLOATERROTCTRL_H
#define SCN_STEP_HERO_FLOATERROTCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class FloaterRotCtrl {
public:
    f32 getRotV() const;
    void initRotV(f32 rot);
    void setRotVTarget(f32 rot);
    void resetRotVTarget();
    void setRotVIntpRate(f32 rate);
    void resetRotVIntpRate();
};

}
}
}

#endif
