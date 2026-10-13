#ifndef SCN_STEP_HERO_FINALBATTLESHADOW_H
#define SCN_STEP_HERO_FINALBATTLESHADOW_H

#include "g3d/NodeAccessor.h"
#include "scn/step/chara/Effect.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {

namespace weapon {
class Weapon;
}

namespace hero {

class Hero;

class FinalBattleShadow {
public:
    FinalBattleShadow(Hero& hero);
    ~FinalBattleShadow();

    void update();
    void setVisibility(bool isVisible);

private:
    void createEffectLocator();
    void killEffectLocator();
    g3d::NodeAccessor node();
    void requestEffect();
    void releaseEffect();
    void onObjStopStarted();
    void onObjStopFinished();
    void pause();
    void unpause();
    void updateIsValid();
    void setIsValid(bool isValid);

    Hero& mHero;
    bool _4;
    bool _5;
    util::ObjRefHandle<weapon::Weapon> mEffectLocator;
    chara::Effect mEffect;
    bool _40;
    bool _41;
};

}}}  // namespace scn::step::hero

#endif
