#ifndef SCN_STEP_ENEMY_EFFECT_H
#define SCN_STEP_ENEMY_EFFECT_H

namespace scn {
namespace step {

namespace chara {

class Effect;

}

namespace enemy {

class Enemy;

// TODO: members and bases.
class Effect {
public:
    Effect(Enemy& enemy);

    chara::Effect& state();
    chara::Effect& normal();
    chara::Effect& super();
    chara::Effect& charaBack();
};

}}}  // namespace scn::step::enemy

#endif
