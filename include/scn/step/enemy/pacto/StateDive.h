#ifndef SCN_STEP_ENEMY_PACTO_STATEDIVE_H
#define SCN_STEP_ENEMY_PACTO_STATEDIVE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace pacto {

class StateDive : public StateBase {
public:
    StateDive(Enemy* enemy);
    virtual void procMove();
    virtual void procObjCollReact();

private:
    int mFrame;
    int mSoundWait;
    bool mIsBite;
};

}}}}  // namespace scn::step::enemy::pacto

#endif
