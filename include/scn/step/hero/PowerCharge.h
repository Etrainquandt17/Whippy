#ifndef SCN_STEP_HERO_POWERCHARGE_H
#define SCN_STEP_HERO_POWERCHARGE_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class PowerCharge {
public:
    void clear();
    bool isChargeAttackReady() const;
    void setCanCharge(bool canCharge);
};

}}}  // namespace scn::step::hero

#endif
