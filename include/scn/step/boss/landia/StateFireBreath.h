#ifndef SCN_STEP_BOSS_LANDIA_STATEFIREBREATH_H
#define SCN_STEP_BOSS_LANDIA_STATEFIREBREATH_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateFireBreath : public StateBase {
public:
    struct Config {
        int _0;
    };

    // TODO: the names of the enumerators.
    enum MouthKind {
        MOUTH_KIND_0,
        MOUTH_KIND_1,
        MOUTH_KIND_2,
        MOUTH_KIND_3,
    };

    StateFireBreath(Boss* boss, Config config);
    virtual ~StateFireBreath();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqFireBreath(MouthKind kind);
};

}}}}  // namespace scn::step::boss::landia

#endif
