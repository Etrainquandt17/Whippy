#ifndef SCN_STEP_ENEMY_COMO_BRAINDIVE_H
#define SCN_STEP_ENEMY_COMO_BRAINDIVE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

class BrainDive : public BrainBase {
public:
    BrainDive(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::como

#endif
