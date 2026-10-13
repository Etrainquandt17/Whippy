#ifndef SCN_STEP_HERO_MINTSTAGINGCTRL_H
#define SCN_STEP_HERO_MINTSTAGINGCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

namespace MintStagingCtrl {

void SetZoom(f32 x, f32 y, f32 rate);
void SetZoom(f32 rate);
void UnsetZoom();
void SetCamRot(f32 x, f32 y);
void UnsetCamRot();

}
}
}
}

#endif
