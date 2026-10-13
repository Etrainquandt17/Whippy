#ifndef SCN_STEP_ENEMY_BRAINCTRL_H
#define SCN_STEP_ENEMY_BRAINCTRL_H

namespace mem {

class IAllocator;

}

namespace scn {
namespace step {
namespace enemy {

class BrainBase;
class Enemy;

// TODO: members.
class BrainCtrl {
public:
    BrainCtrl(Enemy& enemy, mem::IAllocator& allocator);

    void update();
    void toValid();
    bool onStart();
    bool onRecover();
    bool onLanding();
};

}}}  // namespace scn::step::enemy

#endif
