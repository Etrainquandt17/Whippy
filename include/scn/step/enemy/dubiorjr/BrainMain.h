#ifndef SCN_STEP_ENEMY_DUBIORJR_BRAINMAIN_H
#define SCN_STEP_ENEMY_DUBIORJR_BRAINMAIN_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace dubiorjr {

class BrainMain : public BrainBase {
public:
    BrainMain(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::dubiorjr

#endif
