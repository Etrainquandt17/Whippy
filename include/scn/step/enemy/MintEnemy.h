#ifndef SCN_STEP_ENEMY_MINTENEMY_H
#define SCN_STEP_ENEMY_MINTENEMY_H

namespace scn {
namespace step {
namespace enemy {

class Enemy;

class MintEnemy {
public:
    static void Register(Enemy& enemy);
    static void Unregister(Enemy& enemy);
    static Enemy* Obj();
};

}}}  // namespace scn::step::enemy

#endif
