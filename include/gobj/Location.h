#ifndef GOBJ_LOCATION_H
#define GOBJ_LOCATION_H

#include "hel/math/Vector3.h"

namespace gobj {

// TODO: size and members.
class Location {
public:
    hel::math::Vector3 pos() const;
    void setPos(const hel::math::Vector3& pos);
    hel::math::Vector3 prevPos() const;
    void updatePrevPos();
};

}

#endif
