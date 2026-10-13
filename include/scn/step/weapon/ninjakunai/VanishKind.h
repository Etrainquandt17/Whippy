#ifndef SCN_STEP_WEAPON_NINJAKUNAI_VANISHKIND_H
#define SCN_STEP_WEAPON_NINJAKUNAI_VANISHKIND_H

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

// DROP: the kunai comes off a wall and falls, the same way every time. The ROLL kinds start with a random spread
// (StateVanish::isRoll): DROP_ROLL off other ground, REPEL_ROLL flung up off a target it can't hurt.
enum VanishKind {
    VANISH_KIND_DROP,
    VANISH_KIND_DROP_ROLL,
    VANISH_KIND_REPEL_ROLL,
};

}}}}  // namespace scn::step::weapon::ninjakunai

#endif
