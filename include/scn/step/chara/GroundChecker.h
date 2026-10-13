#ifndef SCN_STEP_CHARA_GROUNDCHECKER_H
#define SCN_STEP_CHARA_GROUNDCHECKER_H

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"

namespace scn {
namespace step {
namespace chara {

class GroundChecker {
public:
    bool isFloorValid() const;
    hel::math::Vector2 getFloorPos() const;
    hel::math::Vector3 getFloorPosVector3() const;
    void setIsValid(bool isValid);
    void update();
};

}}}  // namespace scn::step::chara

#endif
