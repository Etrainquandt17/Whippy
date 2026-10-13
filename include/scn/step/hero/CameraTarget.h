#ifndef SCN_STEP_HERO_CAMERATARGET_H
#define SCN_STEP_HERO_CAMERATARGET_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class CameraTarget {
public:
    f32 getFrontViewOffsTarget() const;
    void setZeroIntpRate();
    void setDependSpeed(bool isDepend);
};

}
}
}

#endif
