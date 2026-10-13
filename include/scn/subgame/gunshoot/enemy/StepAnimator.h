#ifndef SCN_SUBGAME_GUNSHOOT_ENEMY_STEPANIMATOR_H
#define SCN_SUBGAME_GUNSHOOT_ENEMY_STEPANIMATOR_H

#include "g3d/ModelAnimAccessor.h"
#include "scn/subgame/common/view/CameraAnimController.h"
#include "scn/subgame/common/view/ModelAccessor.h"
#include "scn/subgame/gunshoot/enemy/AnimParam.h"
#include "scn/subgame/gunshoot/enemy/PlayListSetController.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace enemy {

class StepAnimator {
public:
    void resumeStep();
    const AnimParam& currentAnimParam() const;
    bool isCameraAnimEnable() const;

private:
    bool hasPlayListSet() const { return _E0 != 0; }

    u8 _0[0x4];
    common::view::ModelAccessor* _4;
    common::view::ModelAccessor* _8;
    u8 _C[0x4];
    common::view::CameraAnimController* _10;
    u8 _14[0x44];
    int _58;
    u8 _5C[0x8];
    int _64;
    u8 _68[0x3];
    bool _6B;
    u8 _6C[0x4];
    g3d::ModelAnimAccessor _70;
    g3d::ModelAnimAccessor _78;
    g3d::ModelAnimAccessor _80;
    f32 _88;
    u8 _8C[0x54];
    PlayListSetController* _E0;
};

}
}
}
}

#endif
