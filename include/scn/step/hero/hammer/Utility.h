#ifndef SCN_STEP_HERO_HAMMER_UTILITY_H
#define SCN_STEP_HERO_HAMMER_UTILITY_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace hammer {

class Utility {
public:
    static bool IsHitFrontFloor(Hero& hero);
};

}}}}  // namespace scn::step::hero::hammer

#endif
