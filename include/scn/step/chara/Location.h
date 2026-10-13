#ifndef SCN_STEP_CHARA_LOCATION_H
#define SCN_STEP_CHARA_LOCATION_H

#include "hel/math/Vector3.h"

namespace gobj {

class Location;

}

namespace scn {
namespace step {
namespace chara {

class Location {
public:
    hel::math::Vector3 pos() const;
    hel::math::Vector3 toCenter() const;
    hel::math::Vector3 centerPos() const;
    void setPos(const hel::math::Vector3& pos);
    gobj::Location& location();
    void setToCenter(const hel::math::Vector3& toCenter);
    hel::math::Vector3 prevPos() const;
};

}}}  // namespace scn::step::chara

#endif
