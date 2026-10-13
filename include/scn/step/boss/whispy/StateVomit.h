#ifndef SCN_STEP_BOSS_WHISPY_STATEVOMIT_H
#define SCN_STEP_BOSS_WHISPY_STATEVOMIT_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateVomit : public StateBase {
public:
    StateVomit(Boss* boss, bool isSoft);
    virtual ~StateVomit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsSoft;
};

}}}}  // namespace scn::step::boss::whispy

#endif
