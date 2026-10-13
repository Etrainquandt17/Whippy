#ifndef SCN_STEP_BOSS_WHISPY_STATEFALLENEMY_H
#define SCN_STEP_BOSS_WHISPY_STATEFALLENEMY_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/whispy/ScriptKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateFallEnemy : public StateBase {
public:
    StateFallEnemy(Boss* boss, ScriptKind kind, u32 interval);
    virtual ~StateFallEnemy();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool reqEnemy();

    u32 mInterval;
    u32 mTimer;
};

}}}}  // namespace scn::step::boss::whispy

#endif
