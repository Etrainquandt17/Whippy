#ifndef SCN_STEP_ENEMY_SHADOW_H
#define SCN_STEP_ENEMY_SHADOW_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {

// TODO: members.
class Shadow {
public:
    ~Shadow();

    void update();
    void updateUseGPU();
    void setVisibility(bool isVisible);
    void changeDepth(f32 depth);
    void changeDiameter(f32 diameter);
    void changeMaxHeight(f32 height);
};

}
}
}

#endif
