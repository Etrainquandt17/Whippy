#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_BRAINHOMING_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_BRAINHOMING_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

class BrainHoming : public BrainBase {
public:
    BrainHoming(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::grandlowperbullet

#endif
