#ifndef SCN_STEP_HERO_SUPERICE_SNOWBALL_H
#define SCN_STEP_HERO_SUPERICE_SNOWBALL_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace superice {

// TODO: a stand-in until the unit is written.
class SnowBall {
public:
    SnowBall(Hero& hero);
    ~SnowBall();

    void setup();

private:
    u32 _0[0x44 / 4];
};

}}}}  // namespace scn::step::hero::superice

#endif
