#ifndef GOBJ_TARGET_H
#define GOBJ_TARGET_H

#include "hel/math/Direction3.h"
#include "types.h"

namespace gobj {

// TODO: size and members.
class Target {
public:
    bool isRightDir() const;
    void setIsRightDir(bool isRightDir);
    f32 getSign() const;
    hel::math::Direction3 getDirection3() const;
    void invert();
};

}  // namespace gobj

#endif
