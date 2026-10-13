#ifndef SCN_STEP_ENEMY_NODDY_STATEWALK_H
#define SCN_STEP_ENEMY_NODDY_STATEWALK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace noddy {

class StateWalk : public StateBase {
public:
    StateWalk(Enemy* enemy);
    virtual ~StateWalk();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::noddy

#endif
