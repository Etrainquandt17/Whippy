#ifndef SCN_STEP_ENEMY_WADDLEDEE_STATESMASHEDEND_H
#define SCN_STEP_ENEMY_WADDLEDEE_STATESMASHEDEND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

class StateSmashedEnd : public StateBase {
public:
    StateSmashedEnd(Enemy* enemy);
    virtual ~StateSmashedEnd();
    virtual void procAnim();
    virtual void procFixPos();

private:
    s32 mFrame;
};

}}}}  // namespace scn::step::enemy::waddledee

#endif
