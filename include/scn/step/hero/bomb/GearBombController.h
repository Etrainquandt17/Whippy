#ifndef SCN_STEP_HERO_BOMB_GEARBOMBCONTROLLER_H
#define SCN_STEP_HERO_BOMB_GEARBOMBCONTROLLER_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

namespace bomb {

class GearBombController {
public:
    GearBombController(Hero& hero);
    ~GearBombController();

    bool isHave() const;
    void update();
    void dropBomb();
    void clearBomb();
    void onShowHero();
    void onHideHero();
    void haveBomb();
    void putBomb();
    void swingBomb(const hel::math::Vector2& velocity);

private:
    Hero& mHero;
    bool _4;
    u32 _8;
    u8 _C[0x24];
};

}}}}  // namespace scn::step::hero::bomb

#endif
