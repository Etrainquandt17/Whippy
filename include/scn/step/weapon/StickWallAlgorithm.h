#ifndef SCN_STEP_WEAPON_STICKWALLALGORITHM_H
#define SCN_STEP_WEAPON_STICKWALLALGORITHM_H

namespace scn {
namespace step {
namespace weapon {

class Weapon;

class StickWallAlgorithm {
public:
    StickWallAlgorithm(Weapon& weapon);
    ~StickWallAlgorithm();

    void procMove();
    void procFixPos();
    void pressToWall();

private:
    Weapon& mObj;
};

}}}  // namespace scn::step::weapon

#endif
