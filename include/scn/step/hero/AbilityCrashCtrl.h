#ifndef SCN_STEP_HERO_ABILITYCRASHCTRL_H
#define SCN_STEP_HERO_ABILITYCRASHCTRL_H

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class AbilityCrashCtrl {
public:
    AbilityCrashCtrl();
    ~AbilityCrashCtrl();

    void update();
    void request();
    bool isRequested() const;
    void clearRequested();
};

}}}  // namespace scn::step::hero

#endif
