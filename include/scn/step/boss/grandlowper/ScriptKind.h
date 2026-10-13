#ifndef SCN_STEP_BOSS_GRANDLOWPER_SCRIPTKIND_H
#define SCN_STEP_BOSS_GRANDLOWPER_SCRIPTKIND_H

namespace scn {
namespace step {
namespace boss {
namespace grandlowper {

// TODO: the other values; these are named after the bindings that pass them.
enum ScriptKind {
    ScriptKind_ShotBullet = 7,
    ScriptKind_ShotBulletFast = 8,
    ScriptKind_ShotBulletVeryFast = 9,
    ScriptKind_ShotBulletFastest = 10,
    ScriptKind_FlyingBomb = 15,
    ScriptKind_FlyingBombEnd = 16,
};

}}}}  // namespace scn::step::boss::grandlowper

#endif
