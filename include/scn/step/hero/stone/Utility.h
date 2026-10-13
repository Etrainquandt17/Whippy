#ifndef SCN_STEP_HERO_STONE_UTILITY_H
#define SCN_STEP_HERO_STONE_UTILITY_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace stone {

class Context;

class Utility {
public:
    static void OnStateStartChange(Hero& hero, Context& context);
    static void OnStateEndChange(Hero& hero);
    static void InitRotH(Hero& hero, Context& context);
    static void UpdateSlipRolling(Hero& hero, Context& context);
    static void ProcMoveChange(Hero& hero);
    static void MoveGround(Hero& hero, Context& context);
    static bool IsSlope(Hero& hero);
    static bool ChkCancel(Hero& hero);
};

}}}}  // namespace scn::step::hero::stone

#endif
