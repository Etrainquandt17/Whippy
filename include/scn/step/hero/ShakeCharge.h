#ifndef SCN_STEP_HERO_SHAKECHARGE_H
#define SCN_STEP_HERO_SHAKECHARGE_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

// TODO: members.
class ShakeCharge {
public:
    ShakeCharge(Hero& hero);
    ~ShakeCharge();

    int power() const;
    void reset();
    void setEnv(int, int, int, u32);
    int powerPrev() const;

private:
    u32 _0[0x34 / 4];
};

}}}  // namespace scn::step::hero

#endif
