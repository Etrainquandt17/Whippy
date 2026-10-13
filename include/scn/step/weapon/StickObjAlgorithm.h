#ifndef SCN_STEP_WEAPON_STICKOBJALGORITHM_H
#define SCN_STEP_WEAPON_STICKOBJALGORITHM_H

#include "hel/math/Vector3.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

// TODO: the unit is not written yet; the functions are the ones the map lists.
class StickObjAlgorithm {
public:
    StickObjAlgorithm(Weapon& weapon);
    ~StickObjAlgorithm();

    void procMove();
    void setOffset(const hel::math::Vector3& offset);

private:
    Weapon& mObj;
};

}}}  // namespace scn::step::weapon

#endif
