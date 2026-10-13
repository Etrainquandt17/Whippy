#ifndef SCN_STEP_ENEMY_MUMBIES_BRAINCHASE_H
#define SCN_STEP_ENEMY_MUMBIES_BRAINCHASE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mumbies {

class BrainChase : public BrainBase {
public:
    BrainChase(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::mumbies

#endif
