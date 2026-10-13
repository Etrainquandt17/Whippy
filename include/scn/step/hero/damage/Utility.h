#ifndef SCN_STEP_HERO_DAMAGE_UTILITY_H
#define SCN_STEP_HERO_DAMAGE_UTILITY_H

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace common {
struct ParamReflectWall;
}
namespace damage {

class Utility {
public:
    static void InitTarget(Hero& hero);
    static void InitVelocity(Hero& hero);
    static bool ReflectWallL(Hero& hero);
    static bool ReflectWallS(Hero& hero);
    static bool ReflectWall(Hero& hero, const common::ParamReflectWall& param);
};

}}}}  // namespace scn::step::hero::damage

#endif
